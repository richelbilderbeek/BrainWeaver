//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtbrainweaverdisplay.h"

#include <boost/lexical_cast.hpp>

#include <QHeaderView>
#include <QTableWidget>

#include "conceptmapcompetencies.h"
#include "conceptmapcompetency.h"
#include "conceptmapconcept.h"
#include "conceptmap.h"
#include "conceptmapedge.h"
#include "count_undirected_graph_levels.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "brainweaverfile.h"
#include "brainweaverhelper.h"
#include "conceptmapnode.h"
#include "qtconceptmapcompetency.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::braw::QtDisplay::QtDisplay()
{

}

void ribi::braw::QtDisplay::DisplayRatedConcepts(
  const File& file,
  QTableWidget * const table) const
{
  const auto g = file.GetConceptMap();
  const int sz{static_cast<int>(boost::num_vertices(g))};
  if (sz == 0)
  {
    std::stringstream msg;
    msg << __func__ << ": must have at least one node";
    throw std::invalid_argument(msg.str());
  }
  table->setRowCount(sz - 1); //-1 to skip focus question node at index 0

  const auto vip = vertices(g);
  assert(boost::num_vertices(g) > 0); //Cannot skip first node with focus question if there are no nodes at all
  auto iter = vip.first; ++iter; //Skip first, focus question

  //auto end = vip.second;

  assert(sz >= 1);
  for (int i=1; i!=sz; ++i, ++iter)
  {
    const int row = i-1; //-1 to skip focus question node at index 0
    const ribi::cmap::Concept concept = ribi::cmap::GetNode(*iter,g).GetConcept();
    //Name
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(concept.GetName().c_str());
      table->setVerticalHeaderItem(row,item);
    }
    //Rating complexity
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(concept.GetRatingComplexity()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row,0,item);
    }
    //Rating concreteness
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(concept.GetRatingConcreteness()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row,1,item);
    }
    //Rating specificity
    {
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(QString::number(concept.GetRatingSpecificity()));
      item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      table->setItem(row,2,item);
    }
  }

  table->verticalHeader()->setMinimumWidth(300);
  table->verticalHeader()->setMaximumWidth(300);
  table->setColumnWidth(0,100);
  table->setColumnWidth(1,100);
  table->setColumnWidth(2,100);
  table->setMaximumWidth(
      table->verticalHeader()->width()
    + table->columnWidth(0)
    + table->columnWidth(1)
    + table->columnWidth(2)
  );



}

//Examples' icons
void ribi::braw::QtDisplay::DisplayExamples(
  const File& file,
  QTableWidget * const table) const
{
  {
    const int n_rows = table->rowCount();
    for(int i=0; i!=n_rows; ++i)
    {
      //Skip 0 == uninitialized
      const cmap::Competency competency = static_cast<cmap::Competency>(i + 1);
      const std::string text = cmap::Competencies().ToStrDutch(competency);
      const QIcon icon = cmap::QtCompetency().CompetencyToIcon(competency);
      QTableWidgetItem * const item = new QTableWidgetItem;
      item->setText(text.c_str());
      item->setIcon(icon);
      table->setVerticalHeaderItem(i,item);
    }
  }
  //Examples' competencies
  {
    std::map<cmap::Competency,int> cnts;

    for(const ribi::cmap::Node node: ribi::cmap::GetNodes(file.GetConceptMap()))
    {
      for (const ribi::cmap::Example& example: node.GetConcept().GetExamples().Get())
      {
        const auto iter = cnts.find(example.GetCompetency());
        if (iter != cnts.end())
        {
          ++(*iter).second;
        }
        else
        {
          const cmap::Competency competency = example.GetCompetency();
          cnts.insert(std::make_pair(competency,1));
        }
      }
    }
    const int sum = std::accumulate(cnts.begin(),cnts.end(),0,
      [](int& init,const std::pair<cmap::Competency,int>& p)
      {
        init += p.second;
        return init;
      }
    );
    if (sum != 0)
    {
      for (const std::pair<cmap::Competency,int>& p: cnts)
      {
        const int col = 0;
        const int row = static_cast<int>(p.first) - 1;
        if (row == -1) continue; //0 == uninitialized
        assert(row >= 0);
        assert(row < table->rowCount());
        QTableWidgetItem * const item  = new QTableWidgetItem;
        const double f = static_cast<double>(p.second) / static_cast<double>(sum);
        const int percentage = static_cast<int>(std::round(100.0 * f));
        const std::string text = boost::lexical_cast<std::string>(percentage);
        item->setText(text.c_str());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        table->setItem(row,col,item);
      }
    }
  }
}


void ribi::braw::QtDisplay::DisplayMiscValues(
  const File& file,
  QTableWidget * const table) const
{
  SetNumberOfNodes(file, table);
  auto g = file.GetConceptMap();
  //Average number of connections per non-center node
  {
    std::vector<int> degrees;
    const auto vip = vertices(g);
    for (auto i = vip.first; i != vip.second; ++i)
    {
      if (ribi::cmap::GetNode(*i, g).IsCenterNode()) continue;
      degrees.push_back(boost::degree(*i, g));
    }
    const int sum{std::accumulate(std::begin(degrees), std::end(degrees), 0)};
    const double average_degree_per_concept{
      static_cast<double>(sum) / static_cast<double>(degrees.size())
    };
    const std::string text = boost::lexical_cast<std::string>(average_degree_per_concept);
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(0,1,item);
  }
  //Hierarchical levels
  {
    const auto vd = ribi::cmap::FindCenterNode(g);
    const int n{count_undirected_graph_levels(vd, g)};
    const std::string text{boost::lexical_cast<std::string>(n)};
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(0,2,item);
  }


  //Fixing table
  table->verticalHeader()->setMaximumWidth(300);
  table->verticalHeader()->setMinimumWidth(300);
  table->setColumnWidth(0,300);
  table->setMaximumWidth(
      table->verticalHeader()->width()
    + table->columnWidth(0)
  );
}


void ribi::braw::QtDisplay::DisplayValues(
  const File& file,
  QTableWidget * const table) const
{
  if (boost::num_vertices(file.GetConceptMap()) == 0)
  {
    std::stringstream msg;
    msg << __func__ << ": must have at least one node";
    throw std::invalid_argument(msg.str());
  }

  //The first node removed
  const auto g = RemoveFirstNode(file.GetConceptMap());
  std::vector<ribi::cmap::Node> nodes = ribi::cmap::GetNodes(g);

  const int n_nodes = static_cast<int>(nodes.size());  //Constant 'c'
  //Concreteness experimental: C_e at row = 1, col = 0
  //50.0 * sum_rated_concreteness / n_nodes
  {
    std::string text = "N/A";
    if (n_nodes != 0)
    {
      text = boost::lexical_cast<std::string>(CalculateConcretenessExperimental(file));
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(1,0,item);
  }
  //Concreteness eStimated: C_s at row = 1, col = 1
  //C_s = 100.0 * n_examples / (n_examples + n_nodes + n_relations_not_to_focus)
  {
    const std::vector<ribi::cmap::Edge> edges = GetEdges(file.GetConceptMap());
    const int n_nodes_examples = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const ribi::cmap::Node& node)
      {
        return init + static_cast<int>(node.GetConcept().GetExamples().Get().size());
      }
    );
    const int n_edges_examples = std::accumulate(edges.begin(),edges.end(),0,
      [](int& init, const ribi::cmap::Edge& edge)
      {
        return init + static_cast<int>(edge.GetNode().GetConcept().GetExamples().Get().size());
      }
    );

    //This works, because the focus is already removed
    const int n_relations_not_to_focus{static_cast<int>(boost::num_edges(g))};

    const int n_examples //Constant 'v'
      = n_nodes_examples + n_edges_examples;
    std::string text = "N/A";
    if (n_examples + n_nodes + n_relations_not_to_focus != 0)
    {
      const double c_s
        = static_cast<int>(
          std::round(
            100.0 * static_cast<double>(n_examples)
            / static_cast<double>(n_examples + n_nodes + n_relations_not_to_focus)
          )
        );
      text = boost::lexical_cast<std::string>(c_s);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(1,1,item);
  }
  //Complexity experimental value: X_e at row = 0, col = 0
  //50.0 * sum_rated_complexity / n_nodes
  {
    const int sum_rated_complexity //Constant 'k_i'
      = std::accumulate(nodes.begin(),nodes.end(),0,
      [](int& init, const ribi::cmap::Node& node)
      {
        return init + node.GetConcept().GetRatingComplexity();
      }
    );
    std::string text = "N/A";
    if (n_nodes != 0)
    {
      const int x_e
        = static_cast<int>(
          std::round(
           50.0 * static_cast<double>(sum_rated_complexity)
            / static_cast<double>(n_nodes)
          )
        );
      text = boost::lexical_cast<std::string>(x_e);
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(0,0,item);
  }
  //compleXity eStimated: X_s at row = 0, col = 1
  //x_s = ((2*n_relations_not_to_focus)/(n_nodes*(n_nodes-1))))^0.25*100%
  {
    const std::vector<ribi::cmap::Edge> edges = GetEdges(file.GetConceptMap());
    ///This works, because focal node has already been deleted
    const int n_relations_not_to_focus{static_cast<int>(boost::num_edges(g))}; //Constant 'r'
    std::string text = "N/A";
    if (n_nodes > 1)
    {
      const int x_s
        = static_cast<int>(
            std::round(
              100.0
              * std::pow(
                  static_cast<double>(n_relations_not_to_focus * 2)
                / static_cast<double>(n_nodes * (n_nodes - 1) ),
                0.25)
            )
          );
       text = boost::lexical_cast<std::string>(x_s);
     }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(0,1,item);
  }
  //Experimental specificity: s_e at row = 2, col = 0
  //s_e = 50.0 * sum_rated_specificity / n_nodes
  {
    std::string text = "N/A";
    if (n_nodes != 0)
    {
      text = boost::lexical_cast<std::string>(CalculateSpecificityExperimental(file));
    }
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(2,0,item);
  }
  //Richness Experimental: r_e at row = 3, col = 0
  //r_e = ((a + b) / 14) * 100%
  //a = number of different Competencies
  //b = number of Competencies between 1/12th and 1/4th of number of examples
  {
    const int r_e = CalculateRichnessExperimental(file);
    std::string text = boost::lexical_cast<std::string>(r_e);
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(3,0,item);
  }
  table->verticalHeader()->setMaximumWidth(100);
  table->verticalHeader()->setMinimumWidth(100);
  table->setColumnWidth(0,200);
  table->setColumnWidth(1,200);
  assert(table->verticalHeader()->width() == 100);
  table->setMaximumWidth(
      table->verticalHeader()->width()
    + table->columnWidth(0)
    + table->columnWidth(1)
  );
}


void ribi::braw::QtDisplay::SetNumberOfNodes(
  const File& file,
  QTableWidget * const table) const
{
  const auto g = file.GetConceptMap();
  const std::string text = boost::lexical_cast<std::string>(boost::num_vertices(g));
  QTableWidgetItem * const item = new QTableWidgetItem;
  item->setText(text.c_str());
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  table->setItem(0,0,item);
}
