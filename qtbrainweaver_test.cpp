#include "qtbrainweaver_test.h"

#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverconceptmapdialogcloser.h"
#include "brainweaverfilefactory.h"
#include "qtbrainweaverstudentmenudialog.h"
#include "ui_qtbrainweaverstudentmenudialog.h"

void ribi::braw::QtTest::ModifiedFileAfterEditConceptMapOk() const noexcept
{
  const File file_before = FileFactory().GetUnrated();
  QtClusterDialog d(file_before);
  assert(file_before == d.ToFile());

  d.show();

  QtConceptMapDialogCloser c;
  QSKIP("TODO: Does not work on Travis", "WIP");
  QTimer::singleShot(200, &c, SLOT(Modify()));
  QTimer::singleShot(400, &c, SLOT(PressOk()));
  d.on_button_next_clicked();

  assert("Closed the ConceptMapDialog (would freeze otherwise)");

  const File file_after = d.ToFile();
  QVERIFY(file_before != file_after);
}

void ribi::braw::QtTest::SameFileAfterEditConceptMapCancelled() const noexcept
{
  const File file_before = FileFactory().GetUnrated();
  QtClusterDialog d(file_before);
  assert(file_before == d.ToFile());

  d.show();

  QtConceptMapDialogCloser c;
  QTimer::singleShot(200, &c, SLOT(Modify()));
  QTimer::singleShot(400, &c, SLOT(PressCancel()));
  d.on_button_next_clicked();

  assert("Closed the ConceptMapDialog (would freeze otherwise)");

  const File file_after = d.ToFile();
  QVERIFY(file_before == file_after);
}

void ribi::braw::QtTest::Issue308Cluster() const noexcept
{
  // Create a file for a student, using Developer
  File f = FileFactory().GetFocalQuestionOnly();

  // Load the empty file, fill in name, cluster, save
  QtStudentMenuDialog menu(f);
  menu.SetName("John Doe");
  /*
  QtStudentStartDialogCloser start_closer;
  QtClusterDialogCloser cluster_closer;

  QTimer::singleShot(200, &start_closer, SLOT(PressAssociate()));

  QTimer::singleShot(400, &start_closer, SLOT(Close()));
  */
  // Navigate backwards to menu using OK
  // Navigate forward again

}

void ribi::braw::QtTest::Issue308ConceptMap() const noexcept
{

}
