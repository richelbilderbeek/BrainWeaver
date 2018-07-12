#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtbrainweaverdisplay.h"

#include <tuple>

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
#include "get_my_custom_vertexes.h"
#include "conceptmapexamples.h"
#include "brainweaverfile.h"
#include "brainweaverhelper.h"
#include "conceptmapnode.h"
#include "qtconceptmapcompetency.h"

#pragma GCC diagnostic pop

ribi::braw::QtDisplay::QtDisplay()
{

}

QTableWidget * ribi::braw::QtDisplay::CreateDiagnosticsWidget(
  const File& file,
  QWidget * const parent
) const
{
  auto * const table = new QTableWidget(8, 1, parent);
  //DisplayValues(file, table);
  DisplayMiscValues(file, table);
  //assert(table->rowCount() == 8);
  //assert(table->columnCount() == 1);
  table->verticalHeader()->setMinimumWidth(200);
  table->setMinimumHeight(269);
  table->setMaximumHeight(269);
  table->setMinimumWidth(275);
  table->setMaximumWidth(275);
  table->setColumnWidth(0,70);
  table->setHorizontalHeaderLabels( { "Waarde" } );
  {
    const int row_index{0};
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Complexiteit"));
    table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CalculateComplexityExperimental(file))));
  }
  {
    const int row_index{1};
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Concreetheid"));
    table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CalculateConcretenessExperimental(file))));
  }
  {
    const int row_index{2};
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Specificiteit"));
    table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CalculateSpecificityExperimental(file))));
  }
  {
    const int row_index{3};
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Rijkheid"));
    try
    {
      table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CalculateRichnessExperimental(file))));
    }
    catch (const std::invalid_argument& e)
    {
      //OK, just display nothing
      assert(std::string(e.what()) == "Cannot calculate richness if not all examples are rated");
    }
  }
  {
    const int row_index{4};
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Aantal concepten"));
    table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CountNodes(file))));
  }
  {
    const int row_index{5};
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Relaties per concept"));
    table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CountEdgesPerNode(file))));
  }

  table->setVerticalHeaderItem(6, new QTableWidgetItem("Hierarchische niveaus"));
  table->setVerticalHeaderItem(7, new QTableWidgetItem("Aantal voorbeelden"));

  table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  return table;
}

QTableWidget * ribi::braw::QtDisplay::CreateTalliedExamplesWidget(
  const File& file,
  QWidget * const parent
) const
{
  auto * const table = new QTableWidget(7, 1, parent);
  DisplayExamples(file, table);
  assert(table->rowCount() == 7);
  assert(table->columnCount() == 1);
  table->verticalHeader()->setMinimumWidth(200);
  table->setMinimumHeight(239);
  table->setMaximumHeight(239);
  table->setMinimumWidth(327);
  table->setMaximumWidth(327);
  table->setColumnWidth(0,70);
  table->setHorizontalHeaderLabels( { "%" } );
  table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  return table;
}


void ribi::braw::QtDisplay::DisplayRatedConcepts(
  const File& file,
  QTableWidget * const table
) const
{
  if (!boost::num_vertices(file.GetConceptMap()))
  {
    std::stringstream msg;
    msg << __func__ << ": must have at least one node";
    throw std::invalid_argument(msg.str());
  }

  //The first node, the focal question, removed
  const auto g = RemoveFirstNode(file.GetConceptMap());

  table->setRowCount(boost::num_vertices(file.GetConceptMap()));

  int row = 0;
  for (const ribi::cmap::Node& node: ribi::cmap::GetNodes(g))
  {
    const ribi::cmap::Concept& concept = node.GetConcept();
    DisplayRatedConceptName(concept, table, row);
    DisplayRatedConceptRatingComplexity(concept, table, row, 0);
    DisplayRatedConceptRatingConcreteness(concept, table, row, 1);
    DisplayRatedConceptRatingSpecificity(concept, table, row, 2);
    ++row;
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

void ribi::braw::QtDisplay::DisplayRatedConceptName(
  const ribi::cmap::Concept& concept,
  QTableWidget * const table,
  const int row
) const
{
  QTableWidgetItem * const item = new QTableWidgetItem;
  item->setText(concept.GetName().c_str());
  assert(row >= 0);
  assert(row < table->rowCount());
  table->setVerticalHeaderItem(row,item);
}

void ribi::braw::QtDisplay::DisplayRatedConceptRatingComplexity(
  const ribi::cmap::Concept& concept,
  QTableWidget * const table,
  const int row,
  const int col
) const
{
  QTableWidgetItem * const item = new QTableWidgetItem;
  item->setText(QString::number(concept.GetRatingComplexity()));
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  assert(row >= 0);
  assert(row < table->rowCount());
  assert(col < table->columnCount());
  table->setItem(row,col,item);
}

void ribi::braw::QtDisplay::DisplayRatedConceptRatingConcreteness(
  const ribi::cmap::Concept& concept,
  QTableWidget * const table,
  const int row,
  const int col
) const
{
  QTableWidgetItem * const item = new QTableWidgetItem;
  item->setText(QString::number(concept.GetRatingConcreteness()));
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  assert(row >= 0);
  assert(row < table->rowCount());
  assert(col < table->columnCount());
  table->setItem(row,col,item);
}

void ribi::braw::QtDisplay::DisplayRatedConceptRatingSpecificity(
  const ribi::cmap::Concept& concept,
  QTableWidget * const table,
  const int row,
  const int col
) const
{
  QTableWidgetItem * const item = new QTableWidgetItem;
  item->setText(QString::number(concept.GetRatingSpecificity()));
  item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
  assert(row >= 0);
  assert(row < table->rowCount());
  assert(col < table->columnCount());
  table->setItem(row,col,item);
}

void ribi::braw::QtDisplay::DisplayExamples(
  const File& file,
  QTableWidget * const table) const
{
  assert(table->rowCount() == 7);
  assert(table->columnCount() == 1);
  //Display competency names, with icon
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
  //Display the tallied Examples' competencies
  {
    std::map<cmap::Competency,int> cnts = TallyCompetencies(file);

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
        QTableWidgetItem * const item  = new QTableWidgetItem;
        const double f = static_cast<double>(p.second) / static_cast<double>(sum);
        const int percentage = static_cast<int>(std::round(100.0 * f));
        const std::string text = boost::lexical_cast<std::string>(percentage);
        item->setText(text.c_str());
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        assert(row >= 0);
        assert(row < table->rowCount());
        assert(col < table->columnCount());
        table->setItem(row,col,item);
      }
    }
  }
}


void ribi::braw::QtDisplay::DisplayMiscValues(
  const File& file,
  QTableWidget * const table) const
{
  //SetNumberOfNodes(file, table);
  auto g = file.GetConceptMap();
  //Average number of connections per non-center node
  {
    std::vector<int> degrees;
    const auto vip = vertices(g);
    for (auto i = vip.first; i != vip.second; ++i)
    {
      if (IsCenterNode(g[*i])) continue;
      degrees.push_back(boost::degree(*i, g));
    }
    const int sum{std::accumulate(std::begin(degrees), std::end(degrees), 0)};
    const double adpc{ //average_degree_per_concept
      static_cast<double>(sum) / static_cast<double>(degrees.size())
    };
    const std::string text = boost::lexical_cast<std::string>(adpc);
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    table->setItem(4 + 1,0,item);
  }
  //Hierarchical levels
  {
    const auto vd = ribi::cmap::FindCenterNode(g);
    const int n{count_undirected_graph_levels(vd, g)};
    const std::string text{boost::lexical_cast<std::string>(n)};
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    assert(2 < table->rowCount());
    assert(0 < table->columnCount());
    table->setItem(4 + 2,0,item);
  }
  //Number of examples
  {
    const int n{CountExamples(g)};
    const std::string text{boost::lexical_cast<std::string>(n)};
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setText(text.c_str());
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    assert(3 < table->rowCount());
    assert(0 < table->columnCount());
    table->setItem(4 + 3, 0, item);
  }
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
  assert(0 < table->rowCount());
  assert(0 < table->columnCount());
  table->setItem(4 + 0,0,item);
}
