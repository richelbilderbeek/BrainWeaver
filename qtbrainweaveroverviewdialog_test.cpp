#include "qtbrainweaveroverviewdialog_test.h"
#include "qtbrainweaveroverviewdialog.h"
#include "conceptmaphelper.h"

void ribi::braw::QtBrainWeaverOverviewDialogTest::CloseOnEscape()
{
  QtOverviewDialog d;
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::QtBrainWeaverOverviewDialogTest::Construction()
{
  QtOverviewDialog d;
  d.show();
}
