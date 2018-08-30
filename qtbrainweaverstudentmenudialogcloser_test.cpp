#include "qtbrainweaverstudentmenudialogcloser_test.h"

#include "conceptmapfactory.h"
#include "conceptmaphelper.h"
#include "qtbrainweaverstudentmenudialogcloser.h"
#include "qtbrainweaverstudentmenudialog.h"
#include "brainweaverfilefactory.h"

using namespace ribi::braw;
using namespace ribi::cmap;

void ribi::braw::QtStudentMenuDialogCloserTest::Close() const noexcept
{
  if (OnTravis()) return;

  ribi::braw::QtStudentMenuDialog d(
    FileFactory().GetFocalQuestionOnly()
  );
  QtStudentMenuDialogCloser c;
  QTimer::singleShot(100, &c, SLOT(Close()));
  d.exec();
  QVERIFY(d.isHidden());

}

void ribi::braw::QtStudentMenuDialogCloserTest::PressStart() const noexcept
{
  if (OnTravis()) return;

  ribi::braw::QtStudentMenuDialog d(
    FileFactory().GetFocalQuestionOnly()
  );
  QtStudentMenuDialogCloser c;
  QTimer::singleShot(100, &c, SLOT(PressStart()));
  QTimer::singleShot(200, qApp, SLOT(closeAllWindows()));
  d.exec();
  QVERIFY("Should get here (else the tests froze)");
}
