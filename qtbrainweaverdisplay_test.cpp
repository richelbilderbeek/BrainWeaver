#include "qtbrainweaverdisplay_test.h"

#include <memory>
#include <QTableWidget>
#include "qtbrainweaverdisplay.h"
#include "brainweaverfile.h"
#include "brainweaverfilefactory.h"

void ribi::braw::QtDisplayTest::CreateRatedConceptsWidgetOnEmptyGraphThrows() const noexcept
{
  File f = FileFactory().Get0();
  try
  {
    QtDisplay().CreateRatedConceptsWidget(f);
    assert(!"Should not get here");
  }
  catch (const std::invalid_argument&)
  {
    QVERIFY("Should get here");
  }
}


void ribi::braw::QtDisplayTest::CreateTalliedExamplesWidgetIsReadOnly() const noexcept
{
  const File file = FileFactory().GetRated();
  std::unique_ptr<QTableWidget> w{QtDisplay().CreateTalliedExamplesWidget(file)};
  assert(w);
  const int n_rows{w->rowCount()};
  assert(n_rows == 7);
  assert(w->columnCount() == 1);
  for (int row = 0; row != n_rows; ++row)
  {
    assert(w->item(row, 0));
    const bool is_editable{
      w->item(row, 0)->flags() & Qt::ItemIsEditable
    };
    assert(!is_editable);
    QVERIFY(!is_editable);
  }
}
