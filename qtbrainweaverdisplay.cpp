#include "qtbrainweaverdisplay.h"

#include <QHeaderView>
#include <QTableWidget>

#include "brainweaverfile.h"
#include "brainweaverhelper.h"
#include "conceptmapcompetencies.h"
#include "qtconceptmapcompetency.h"

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

  const QVector<QString> header_texts = {
    "Complexiteit (%)",
    "Concreetheid (%)",
    "Specificiteit (%)",
    "Rijkheid (%)",
    "Aantal concepten",
    "Aantal relaties",
    "Relaties per concept",
    "Hierarchische niveaus",
    "Aantal voorbeelden"
  };

  const QVector<QString> tooltip_texts = {
      "De waarde van k_i in [1]\nk_i = 0.5 * de som van de gescoorde complexiteit van de concepten\ngedeeld door het aantal concepten\n\n[1] ACM van den Bogaart et al., 2016", //!OCLINT I want to put one tooltip text per line
      "0.5 * de som van de gescoorde concreetheid van de concepten\ngedeeld door het aantal concepten", //!OCLINT I want to put one tooltip text per line
      "0.5 * de som van de gescoorde specificiteit van de concepten\ngedeeld door het aantal concepten", //!OCLINT I want to put one tooltip text per line
      "Rijkheid van de voorbeelden, iets met 'a + b / 12.0'",
      "Aantal concepten (exclusief focusvraag)",
      "Aantal verbindingen (inclusief verbindingen met de focusvraag)",
      "Gemiddeld aantal verbindingen\nmet andere concepten (niet de focusvraag)\nper concept (exclusief focusvraag)", //!OCLINT I want to put one tooltip text per line
      "De diepte van de concept map:\n * enkel focusvraag = 0\n * enkel concepten verbonden met focusvraag = 1\n * concept verbonden aan concepten verbonden aan focusvraag = 2\n * etcetera", //!OCLINT I want to put one tooltip text per line
      "Het totaal aantal voorbeelden"
  };

  QVector<QString> values = {
    QString::number(CalculateComplexityExperimental(file)),
    QString::number(CalculateConcretenessExperimental(file)),
    QString::number(CalculateSpecificityExperimental(file)),
    "",
    QString::number(CountNodes(file) - 1),
    QString::number(CountEdges(file)),
    QString::number(CountEdgesPerNormalNode(file)),
    QString::number(CountHierarchicalLevels(file)),
    QString::number(CountExamples(file))
  };

  for (int row_index = 0; row_index != 9; ++row_index)
  {
    auto * const headerItem = new QTableWidgetItem(header_texts[row_index]);
    headerItem->setToolTip(tooltip_texts[row_index]);
    table->setVerticalHeaderItem(row_index, headerItem);
    auto * const item = new QTableWidgetItem(values[row_index]);
    item->setToolTip(tooltip_texts[row_index]);
    table->setItem(row_index, 0, item);
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
  if (!boost::num_vertices(file.GetConceptMap()))
  {
    std::stringstream msg;
    msg << __func__ << ": must have at least one node";
    throw std::invalid_argument(msg.str());
  }

  auto * const table = new QTableWidget(0, 3, parent);

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
  table->setWordWrap(true);
  //table->setMaximumWidth(650);
  table->setMinimumWidth(650);
  table->setHorizontalHeaderLabels( { "X", "S", "C" } );
  table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  table->verticalHeader()->setMaximumWidth(530);
  table->verticalHeader()->setTextElideMode(Qt::TextElideMode::ElideNone);
  table->setSizeAdjustPolicy(
    QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents
  );
  table->verticalHeader()->resizeSections(
    QHeaderView::ResizeMode::ResizeToContents
  );
  table->resizeRowsToContents();
  table->setMinimumHeight(
    table->sizeHint().height()
  );
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
  const int w = 45;
  table->setMinimumWidth(285 + w);
  table->setMaximumWidth(285 + w);
  table->setColumnWidth(0, w);
  table->setHorizontalHeaderLabels( { "%" } );
  table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  return table;
}



void ribi::braw::QtDisplay::DisplayRatedConceptName(
  const ribi::cmap::Concept& concept,
  QTableWidget * const table,
  const int row
) const
{
  QTableWidgetItem * const item =
    new QTableWidgetItem(concept.GetName().c_str());
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

    const int sum = std::accumulate(cnts.begin(), cnts.end(), 0,
      [](int& init, const std::pair<cmap::Competency, int>& p)
      {
        init += p.second;
        return init;
      }
    );
    if (sum != 0)
    {
      for (const std::pair<cmap::Competency, int>& p: cnts)
      {
        const int col = 0;
        const int row = static_cast<int>(p.first) - 1;
        if (row == -1) continue; //0 == uninitialized
        QTableWidgetItem * const item  = new QTableWidgetItem;
        const double f{
          static_cast<double>(p.second)
          / static_cast<double>(sum)
        };
        const int percentage = static_cast<int>(std::round(100.0 * f));
        item->setText(QString::number(percentage));
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setTextAlignment(Qt::AlignCenter);
        assert(row >= 0);
        assert(row < table->rowCount());
        assert(col < table->columnCount());
        table->setItem(row, col, item);
      }
    }
  }
}
