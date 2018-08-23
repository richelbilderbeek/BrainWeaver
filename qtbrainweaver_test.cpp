#include "qtbrainweaver_test.h"

#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "brainweaverfilefactory.h"


void ribi::braw::QtTest::ModifiedFileAfterEditConceptMapOk() const noexcept
{
  File f = FileFactory().GetUnrated();
  QtClusterDialog d(f);
  d.show();
  d.on_button_next_clicked();
  assert(qobject_cast<QtConceptMapDialog*>(qApp->activeWindow()));
  assert(1 == 2);

}

void ribi::braw::QtTest::SameFileAfterEditConceptMapCancelled() const noexcept
{
  //
}

void ribi::braw::QtTest::Issue308() const noexcept
{
  //
}
