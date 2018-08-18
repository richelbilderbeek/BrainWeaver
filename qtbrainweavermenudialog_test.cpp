#include "qtbrainweavermenudialog_test.h"

#include <QDebug>
#include "qtbrainweavermenudialog.h"

void ribi::braw::QtBrainWeaverMenuDialogTest::Construction()
{
  auto menu{std::make_unique<ribi::braw::QtMenuDialog>()};
  menu->show();
  //QTest::keyClick(&d,Qt::Key_Escape, Qt::NoModifier);
}

void ribi::braw::QtBrainWeaverMenuDialogTest::PressAllKeys()
{

  //Press digit
  for (int k = static_cast<int>(Qt::Key_0); k <= static_cast<int>(Qt::Key_9); ++k)
  {
    //if (k == Qt::Key_1) continue;
    auto d{std::make_unique<ribi::braw::QtMenuDialog>()};
    d->show();
    QTimer::singleShot(2000, qApp, SLOT(closeAllWindows()));
    QTest::keyClick(d.get(), static_cast<Qt::Key>(k), Qt::AltModifier, 100);
  }
  //Press characters
  for (int k = static_cast<int>(Qt::Key_A); k <= static_cast<int>(Qt::Key_I); ++k)
  {
    auto d{std::make_unique<ribi::braw::QtMenuDialog>()};
    d->show();
    QTimer::singleShot(2000, qApp, SLOT(closeAllWindows()));
    QTest::keyClick(d.get(), static_cast<Qt::Key>(k), Qt::AltModifier, 100);
  }

}
