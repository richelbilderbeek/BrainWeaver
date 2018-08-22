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
