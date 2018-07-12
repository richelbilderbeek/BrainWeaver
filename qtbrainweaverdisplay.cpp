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
  auto * const table = new QTableWidget(9, 1, parent);
  table->verticalHeader()->setMinimumWidth(200);
  table->setMinimumHeight(299);
  table->setMaximumHeight(299);
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
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Aantal relaties"));
    table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CountEdges(file))));
  }
  {
    const int row_index{6};
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Relaties per concept"));
    table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CountEdgesPerNormalNode(file))));
  }
  {
    const int row_index{7};
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Hierarchische niveaus"));
    table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CountHierarchicalLevels(file))));
  }
  {
    const int row_index{8};
    table->setVerticalHeaderItem(row_index, new QTableWidgetItem("Aantal voorbeelden"));
    table->setItem(row_index, 0, new QTableWidgetItem(QString::number(CountExamples(file))));
  }
  table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  return table;
}

QTableWidget * ribi::braw::QtDisplay::CreateRatedConceptsWidget(
  const File& file,
  QWidget * const parent
) const
{
  auto * const table = new QTableWidget(0, 3, parent);
  DisplayRatedConcepts(file, table);
  table->setHorizontalHeaderLabels( { "X", "S", "C" } );
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

  table->setRowCount(boost::num_vertices(g));
  assert(table->columnCount() == 3);
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
  table->setColumnWidth(0, 50);
  table->setColumnWidth(1, 50);
  table->setColumnWidth(2, 50);
  table->setMinimumWidth(
      table->verticalHeader()->width()
    + table->columnWidth(0)
    + table->columnWidth(1)
    + table->columnWidth(2)
  );
  table->setSizeAdjustPolicy(
    QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents
  );
  table->resizeRowsToContents();
  table->setMinimumHeight(
    table->sizeHint().height()
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
