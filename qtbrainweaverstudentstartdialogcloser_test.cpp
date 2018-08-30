#include "qtbrainweaverstudentstartdialogcloser_test.h"

#include "conceptmapfactory.h"
#include "conceptmaphelper.h"
#include "qtbrainweaverstudentstartdialogcloser.h"
#include "qtbrainweaverstudentstartdialog.h"
#include "brainweaverfilefactory.h"

using namespace ribi::braw;
using namespace ribi::cmap;

void ribi::braw::QtStudentStartDialogCloserTest::Close() const noexcept
{
  if (OnTravis()) return;

  ribi::braw::QtStudentStartDialog d(
    FileFactory().GetFocalQuestionOnly()
  );
  QtStudentStartDialogCloser c;
  QTimer::singleShot(100, &c, SLOT(Close()));
  d.exec();
  QVERIFY(d.isHidden());

}

void ribi::braw::QtStudentStartDialogCloserTest::PressStartCluster() const noexcept
{
  if (OnTravis()) return;

  ribi::braw::QtStudentStartDialog d(
    FileFactory().GetFocalQuestionOnly()
  );
  QtStudentStartDialogCloser c;
  QTimer::singleShot(100, &c, SLOT(PressStartCluster()));
  QTimer::singleShot(200, qApp, SLOT(closeAllWindows()));
  d.exec();
  QVERIFY("Should get here (else the tests froze)");
}

void ribi::braw::QtStudentStartDialogCloserTest::PressStartConceptMap() const noexcept
{
  if (OnTravis()) return;

  ribi::braw::QtStudentStartDialog d(
    FileFactory().GetFocalQuestionOnly()
  );
  QtStudentStartDialogCloser c;
  QTimer::singleShot(100, &c, SLOT(PressStartConceptMap()));
  QTimer::singleShot(200, qApp, SLOT(closeAllWindows()));
  d.exec();
  QVERIFY("Should get here (else the tests froze)");
}
