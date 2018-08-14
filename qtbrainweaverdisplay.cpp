#include "qtbrainweaverdisplay.h"

#include <QHeaderView>
#include <QTableWidget>

#include "brainweaverfile.h"
#include "brainweaverhelper.h"
#include "conceptmapcompetencies.h"
#include "qtconceptmapcompetency.h"

QVector<QString> GetDisplayDiagnosticsTooltips() //!OCLINT indeed this is a long function
{
  return {
      "Deze waarde is:\n"
      "\n"
      "100% * (Sx / n) * (1 / 2)\n"
      "\n"
      " * Sx = de som van de gescoorde complexiteit van de concepten\n"
      " * n = het aantal concepten\n"
      "\n"
      "Omdat een complexiteit gescoord kan worden met een waarde van 0 t/m 2,\n"
      "wordt deze som door twee gedeeld.\n"
      "\n"
      "Indien alle complexiteiten gescoord zijn,\n"
      "zal dit getal een waarde van 0 t/m 100% hebben.\n"
      "\n"
      "Dit getal kan een negatieve waarde hebben,\n"
      "als niet alle complexiteiten gescoord zijn."
    ,
      "Deze waarde is:\n"
      "\n"
      "100% * (Sc / n) * (1 / 2)\n"
      "\n"
      " * Sc = de som van de gescoorde concreetheid van de concepten\n"
      " * n = het aantal concepten\n"
      "\n"
      "Omdat een concreetheid gescoord kan worden met een waarde van 0 t/m 2,\n"
      "wordt deze som door twee gedeeld.\n"
      "\n"
      "Indien alle concreetheden gescoord zijn,\n"
      "zal dit getal een waarde van 0 t/m 100% hebben.\n"
      "\n"
      "Dit getal kan een negatieve waarde hebben,\n"
      "als niet alle concreetheden gescoord zijn."
    ,
      "Deze waarde is:\n"
      "\n"
      "100% * (Ss / n) * (1 / 2)\n"
      "\n"
      " * Ss = de som van de gescoorde specificiteit van de concepten\n"
      " * n = het aantal concepten\n"
      "\n"
      "Omdat een specificiteit gescoord kan worden met een waarde van 0 t/m 2,\n"
      "wordt deze som door twee gedeeld.\n"
      "\n"
      "Indien alle specificiteiten gescoord zijn,\n"
      "zal dit getal een waarde van 0 t/m 100% hebben.\n"
      "\n"
      "Dit getal kan een negatieve waarde hebben,\n"
      "als niet alle specificiteiten gescoord zijn."
    ,
      "Deze waarde is, uit [1]:\n"
      "\n"
      "100% * ((a /12) + (b / 12))\n"
      "\n"
      "Zie [1] van de exacte berekening.\n"
      "\n"
      "[1] van den Bogaart, Antoine CM, et al.\n"
      "    \"A computer-supported method to reveal and assess \n"
      "    Personal Professional Theories in vocational education.\"\n"
      "    Technology, pedagogy and education 25.5 (2016): 613-629."
    ,
    "Aantal concepten",
    "Aantal concepten verbonden met de focusvraag",
    "Aantal concepten niet verbonden met focusvraag",
    "Aantal verbindingen (inclusief verbindingen met de focusvraag)"
    ,
      "Gemiddeld aantal verbindingen\nmet andere concepten (niet de focusvraag)\n"
      "per concept (exclusief focusvraag)"
    ,
      "De diepte van de concept map:\n"
      "\n"
      " * enkel focusvraag = 0\n"
      " * enkel concepten verbonden met focusvraag = 1\n"
      " * concept verbonden aan concepten verbonden aan focusvraag = 2\n"
      " * etcetera"
    ,
    "Het totaal aantal voorbeelden"
  };
}


ribi::braw::QtDisplay::QtDisplay()
{

}

QTableWidget * ribi::braw::QtDisplay::CreateDiagnosticsWidget(
  const File& file,
  QWidget * const parent
) const
{
  const int n_rows{11};
  auto * const table = new QTableWidget(n_rows, 1, parent);
  table->setHorizontalHeaderLabels( { "Waarde" } );
  DisplayDiagnosticsHeader(table);
  DisplayDiagnosticsItems(file, table);

  //Prevents the horizontal header extending to the right
  table->setSizePolicy(
    QSizePolicy::Policy::Maximum,
    QSizePolicy::Policy::Preferred
  );
  table->setSizeAdjustPolicy(QHeaderView::AdjustToContents);
  table->resizeColumnsToContents();
  table->resizeRowsToContents();
  return table;
}

void ribi::braw::QtDisplay::DisplayDiagnosticsHeader(QTableWidget * const table) const
{
  const int n_rows{table->rowCount()};
  assert(n_rows == 11);

  const QVector<QString> header_texts = {
    "Complexiteit (%)",
    "Concreetheid (%)",
    "Specificiteit (%)",
    "Rijkheid (%)",
    "Aantal concepten",
    "Aantal primaire concepten",
    "Aantal secundaire concepten",
    "Aantal relaties",
    "Relaties per concept",
    "Hierarchische niveaus",
    "Aantal voorbeelden"
  };
  assert(n_rows == static_cast<int>(header_texts.size()));

  const auto tooltip_texts = GetDisplayDiagnosticsTooltips();
  assert(n_rows == static_cast<int>(tooltip_texts.size()));

  for (int row_index = 0; row_index != n_rows; ++row_index)
  {
    auto * const headerItem = new QTableWidgetItem(header_texts[row_index]);
    headerItem->setToolTip(tooltip_texts[row_index]);
    table->setVerticalHeaderItem(row_index, headerItem);
  }
}

void ribi::braw::QtDisplay::DisplayDiagnosticsItems(
  const File& file, QTableWidget * const table) const
{
  const int n_rows{table->rowCount()};
  assert(n_rows == 11);

  QVector<QString> values = {
    QString::number(CalculateComplexityExperimental(file)),
    QString::number(CalculateConcretenessExperimental(file)),
    QString::number(CalculateSpecificityExperimental(file)),
    "",
    QString::number(CountNodes(file) - 1),
    QString::number(CountPrimaryConcepts(file)),
    QString::number(CountSecondaryConcepts(file)),
    QString::number(CountEdges(file)),
    QString::number(CountEdgesPerNormalNode(file)),
    QString::number(CountHierarchicalLevels(file)),
    QString::number(CountExamples(file))
  };
  assert(n_rows == values.size());
  try
  {
    values[3] = QString::number(CalculateRichness(file));
  }
  catch (const std::exception& e)
  {
    assert(std::string(e.what())
      == "Cannot calculate richness if not all examples are rated"
    );
  }

  const auto tooltip_texts = GetDisplayDiagnosticsTooltips();
  assert(n_rows == static_cast<int>(tooltip_texts.size()));

  for (int row_index = 0; row_index != n_rows; ++row_index)
  {
    auto * const item = new QTableWidgetItem(values[row_index]);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setToolTip(tooltip_texts[row_index]);
    table->setItem(row_index, 0, item);
  }
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
  table->setMinimumWidth(650);
  table->setHorizontalHeaderLabels( { "X", "S", "C" } );
  table->verticalHeader()->setTextElideMode(Qt::TextElideMode::ElideNone);
  table->setSizeAdjustPolicy(
    QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents
  );

  //Prevents the horizontal header extending to the right
  table->setSizePolicy(
    QSizePolicy::Policy::Maximum,
    QSizePolicy::Policy::Preferred
  );

  table->resizeRowsToContents();
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
  table->setHorizontalHeaderLabels( { "%" } );

  //Prevents the horizontal header extending to the right
  table->setSizePolicy(
    QSizePolicy::Policy::Maximum,
    QSizePolicy::Policy::Preferred
  );
  table->setSizeAdjustPolicy(QHeaderView::AdjustToContents);
  table->resizeColumnsToContents();
  table->resizeRowsToContents();

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
  DisplayExamplesHeader(table);
  DisplayExamplesItems(file, table);
}

void ribi::braw::QtDisplay::DisplayExamplesHeader(
  QTableWidget * const table) const
{
  assert(table->rowCount() == 7);
  assert(table->columnCount() == 1);
  //Display competency names, with icon
  const int n_rows = table->rowCount();
  for(int i=0; i!=n_rows; ++i)
  {
    //Skip 0 == uninitialized
    const cmap::Competency competency = static_cast<cmap::Competency>(i + 1);
    const std::string text = cmap::Competencies().ToStrDutch(competency);
    const QIcon icon = cmap::QtCompetency().CompetencyToIcon(competency);
    QTableWidgetItem * const item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(text.c_str());
    item->setIcon(icon);
    item->setToolTip(
      ribi::cmap::Competencies().ToStrDutchShort(competency).c_str()
    );
    table->setVerticalHeaderItem(i,item);
  }
}

void ribi::braw::QtDisplay::DisplayExamplesItems(
  const File& file,
  QTableWidget * const table) const
{
  assert(table->rowCount() == 7);
  assert(table->columnCount() == 1);
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
