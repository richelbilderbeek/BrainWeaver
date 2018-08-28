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
  QtStudentStartDialogCloser c;

  if (OnTravis()) return;

  QTimer::singleShot(100, &c, SLOT(Close()));
  ribi::braw::QtStudentStartDialog d(
    FileFactory().GetFocalQuestionOnly()
  );
  d.exec();
  QVERIFY(d.isHidden());

}

void ribi::braw::QtStudentStartDialogCloserTest::PressStartCluster() const noexcept
{
  QtStudentStartDialogCloser c;

  if (OnTravis()) return;

  QTimer::singleShot(100, &c, SLOT(PressStartCluster()));
  ribi::braw::QtStudentStartDialog d(
    FileFactory().GetFocalQuestionOnly()
  );
  d.exec();
  qApp->closeAllWindows();
  QVERIFY("Should get here (else the tests froze)");
}

void ribi::braw::QtStudentStartDialogCloserTest::PressStartConceptMap() const noexcept
{
  QtStudentStartDialogCloser c;

  if (OnTravis()) return;

  QTimer::singleShot(100, &c, SLOT(PressStartConceptMap()));
  ribi::braw::QtStudentStartDialog d(
    FileFactory().GetFocalQuestionOnly()
  );
  d.exec();
  qApp->closeAllWindows();
  QVERIFY("Should get here (else the tests froze)");
}
