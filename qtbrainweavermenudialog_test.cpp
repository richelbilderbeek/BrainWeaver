#include "qtbrainweavermenudialog_test.h"

#include <QDebug>
#include "qtbrainweavermenudialog.h"

void ribi::braw::qtbrainweavermenudialog_test::default_construction()
{
  auto menu{std::make_unique<ribi::braw::QtMenuDialog>()};
  menu->show();
  //QTest::keyClick(&d,Qt::Key_Escape, Qt::NoModifier);
}

void ribi::braw::qtbrainweavermenudialog_test::press_all_keys()
{
  auto d{std::make_unique<ribi::braw::QtMenuDialog>()};
  d->show();

  //Press digit
  for (int k = static_cast<int>(Qt::Key_0); k <= static_cast<int>(Qt::Key_9); ++k)
  {
    if (k == Qt::Key_1) continue;
    QTimer::singleShot(1000, qApp, SLOT(closeAllWindows()));
    QTest::keyClick(d.get(), static_cast<Qt::Key>(k), Qt::AltModifier, 100);
    QTest::keyClick(d.get(), Qt::Key::Key_Escape, Qt::NoModifier, 100);
    QTest::keyClick(d.get(), Qt::Key::Key_Escape, Qt::NoModifier, 100);
  }
  //Press characters
  for (int k = static_cast<int>(Qt::Key_A); k <= static_cast<int>(Qt::Key_H); ++k)
  {
    if (k == Qt::Key_N) continue;
    QTimer::singleShot(1000, qApp, SLOT(closeAllWindows()));
    QTest::keyClick(d.get(), static_cast<Qt::Key>(k), Qt::AltModifier, 100);
    QTest::keyClick(d.get(), Qt::Key::Key_Escape, Qt::NoModifier, 100);
    QTest::keyClick(d.get(), Qt::Key::Key_Escape, Qt::NoModifier, 100);
  }

}
