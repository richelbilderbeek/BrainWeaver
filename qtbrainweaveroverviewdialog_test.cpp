#include "qtbrainweaveroverviewdialog_test.h"
#include "qtbrainweaveroverviewdialog.h"
#include "conceptmaphelper.h"

void ribi::braw::qtbrainweaveroverviewdialog_test::default_construction()
{
  if (!ribi::cmap::OnTravis())
  {
    ribi::braw::QtOverviewDialog d;
    d.show();
  }
}
