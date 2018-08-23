#include "qtbrainweaverconceptmapdialogcloser_test.h"

#include "conceptmapfactory.h"
#include "conceptmaphelper.h"
#include "qtbrainweaverconceptmapdialogcloser.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "brainweaverfilefactory.h"

using namespace ribi::braw;
using namespace ribi::cmap;

void ribi::braw::QtConceptMapDialogCloserTest::Close() const noexcept
{
  QtConceptMapDialogCloser c;

  if (OnTravis()) return;

  QTimer::singleShot(100, &c, SLOT(Close()));
  ribi::braw::QtConceptMapDialog d(
    FileFactory().GetUnrated()
  );
  d.exec();
  QVERIFY("Closed the dialog (would freeze otherwise)");
}
