#include "qtbrainweaverstudentmenudialog_test.h"

#include "brainweaverfile.h"
#include "qtbrainweaverstudentmenudialog.h"

void ribi::braw::qtbrainweaverstudentmenudialog_test::default_construction()
{
  File f;
  QtStudentMenuDialog d(f);
  d.show();
}
