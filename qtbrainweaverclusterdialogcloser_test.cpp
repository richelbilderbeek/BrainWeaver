#include "qtbrainweaverclusterdialogcloser_test.h"

#include "conceptmapfactory.h"
#include "conceptmaphelper.h"
#include "qtbrainweaverclusterdialogcloser.h"
#include "qtbrainweaverclusterdialog.h"
#include "brainweaverfilefactory.h"

using namespace ribi::braw;
using namespace ribi::cmap;

void ribi::braw::QtClusterDialogCloserTest::PressCancel() const noexcept
{
  QtClusterDialogCloser c;

  if (OnTravis()) return;

  QTimer::singleShot(100, &c, SLOT(PressCancel()));
  ribi::braw::QtClusterDialog d(
    FileFactory().GetUnrated()
  );
  d.exec();
  QVERIFY(!d.HasClickedOk());
}

void ribi::braw::QtClusterDialogCloserTest::PressOk() const noexcept
{
  QtClusterDialogCloser c;

  if (OnTravis()) return;

  QTimer::singleShot(100, &c, SLOT(PressOk()));
  ribi::braw::QtClusterDialog d(
    FileFactory().GetUnrated()
  );
  d.exec();
  QVERIFY(d.HasClickedOk());
}
