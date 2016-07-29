#include "qtbrainweaverstudentstartcompletedialog_test.h"

#include "brainweaverfile.h"
#include "qtbrainweaverstudentstartcompletedialog.h"

void ribi::braw::qtbrainweaverstudentstartcompletedialog_test::default_construction()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
}
