#include "qtbrainweaverprintconceptmapdialog_test.h"

#include <cassert>
#include "qtbrainweaverprintconceptmapdialog.h"
#include "brainweaverfilefactory.h"

void ribi::pvdb::qtbrainweaverprintconceptmapdialog_test::default_construct()
{
  const auto files = FileFactory().GetTests();
  for (const auto file: files) {
    QtPvdbPrintConceptMapDialog d(file);
    d.show();
    QTest::qWaitForWindowActive(&d, 1000);
    QTest::qWait(1000);
  }
}
