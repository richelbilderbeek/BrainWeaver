#include "qtbrainweaver_test.h"

#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverconceptmapdialogcloser.h"
#include "brainweaverfilefactory.h"


void ribi::braw::QtTest::ModifiedFileAfterEditConceptMapOk() const noexcept
{
  const File file_before = FileFactory().GetUnrated();
  QtClusterDialog d(file_before);
  assert(file_before == d.ToFile());

  d.show();

  QtConceptMapDialogCloser c;
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

void ribi::braw::QtTest::Issue308() const noexcept
{
  //
}
