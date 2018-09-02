#include "qtbrainweaverfiledialogcloser_test.h"

#include <QFileDialog>

#include "conceptmapfactory.h"
#include "conceptmaphelper.h"
#include "qtbrainweaverfiledialogcloser.h"
#include "qtbrainweaverfiledialog.h"
#include "brainweaverfilefactory.h"
#include "brainweaverfile.h"
using namespace ribi::braw;
using namespace ribi::cmap;

void ribi::braw::QtFileDialogCloserTest::PressCancel() const noexcept
{
  if (OnTravis()) return;

  QtFileDialogCloser c("test.cmp");

  QTimer::singleShot(100, &c, SLOT(PressCancel()));
  QFileDialog d;
  d.exec();
  QVERIFY("Should get here, program freezes otherwise");
  QVERIFY(d.result() == QDialog::Rejected);
}

void ribi::braw::QtFileDialogCloserTest::PressOk() const noexcept
{
  if (OnTravis()) return;

  QtFileDialogCloser c("test.cmp");

  QTimer::singleShot(100, &c, SLOT(PressOk()));
  QFileDialog d;
  d.exec();
  QVERIFY("Should get here, program freezes otherwise");
  QVERIFY(d.result() == QDialog::Accepted);
}
