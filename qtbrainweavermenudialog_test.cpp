#include "qtbrainweavermenudialog_test.h"

#include <QDebug>
#include "qtbrainweavermenudialog.h"
#include "qtbrainweavermasterdialog.h"

void ribi::braw::qtbrainweavermenudialog_test::default_construction()
{
  ribi::braw::QtMasterDialog d;
  d.add_new(new ribi::braw::QtMenuDialog);
  d.show();
  //QTest::keyClick(&d,Qt::Key_Escape, Qt::NoModifier);
}

void ribi::braw::qtbrainweavermenudialog_test::press_all_keys()
{
  //Press digit
  for (int k = static_cast<int>(Qt::Key_0); k <= static_cast<int>(Qt::Key_9); ++k)
  {
    if (k == Qt::Key_1) continue;
    ribi::braw::QtMasterDialog d;
    d.add_new(new ribi::braw::QtMenuDialog);
    d.show();
    QTimer::singleShot(1000, qApp, SLOT(closeAllWindows()));
    QTest::keyClick(&d, static_cast<Qt::Key>(k), Qt::AltModifier, 100);
    QTest::keyClick(&d, Qt::Key::Key_Escape, Qt::NoModifier, 100);
    QTest::keyClick(&d, Qt::Key::Key_Escape, Qt::NoModifier, 100);
  }
  //Press characters
  for (int k = static_cast<int>(Qt::Key_A); k <= static_cast<int>(Qt::Key_H); ++k)
  {
    if (k == Qt::Key_N) continue;
    ribi::braw::QtMasterDialog d;
    d.add_new(new ribi::braw::QtMenuDialog);
    d.show();
    QTimer::singleShot(1000, qApp, SLOT(closeAllWindows()));
    QTest::keyClick(&d, static_cast<Qt::Key>(k), Qt::AltModifier, 100);
    QTest::keyClick(&d, Qt::Key::Key_Escape, Qt::NoModifier, 100);
    QTest::keyClick(&d, Qt::Key::Key_Escape, Qt::NoModifier, 100);
  }

}
