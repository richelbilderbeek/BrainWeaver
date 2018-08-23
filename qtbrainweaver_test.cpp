#include "qtbrainweaver_test.h"

#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverconceptmapdialogcloser.h"
#include "brainweaverfilefactory.h"


void ribi::braw::QtTest::ModifiedFileAfterEditConceptMapOk() const noexcept
{
  File f = FileFactory().GetUnrated();
  QtClusterDialog d(f);
  d.show();


  QtConceptMapDialogCloser c;
  QTimer::singleShot(100, &c, SLOT(Close()));
  d.on_button_next_clicked();

  assert("Closed the ConceptMapDialog (would freeze otherwise)");
}

void ribi::braw::QtTest::SameFileAfterEditConceptMapCancelled() const noexcept
{
  //
}

void ribi::braw::QtTest::Issue308() const noexcept
{
  //
}
