#include "qtbrainweavermenudialog_test.h"
#include "qtbrainweavermenudialog.h"

void ribi::braw::qtbrainweavermenudialog_test::default_construction()
{
  ribi::braw::QtMenuDialog d;
  d.show();
}

void ribi::braw::qtbrainweavermenudialog_test::press_all_keys()
{
  //Press A-Z
  for (int k = static_cast<int>(Qt::Key_A); k <= static_cast<int>(Qt::Key_Z); ++k)
  {
    ribi::braw::QtMenuDialog d;
    d.show();
    QTest::keyClick(&d, static_cast<Qt::Key>(k), Qt::ControlModifier, 100);
    QTest::keyClick(&d, Qt::Key::Key_F4, Qt::AltModifier, 100);
    QTest::keyClick(&d, Qt::Key::Key_F4, Qt::AltModifier, 100);
  }
  //Press 0-9
  for (int k = static_cast<int>(Qt::Key_0); k <= static_cast<int>(Qt::Key_9); ++k)
  {
    ribi::braw::QtMenuDialog d;
    d.show();
    QTest::keyClick(&d, static_cast<Qt::Key>(k), Qt::ControlModifier, 100);
    QTest::keyClick(&d, Qt::Key::Key_F4, Qt::AltModifier, 100);
    QTest::keyClick(&d, Qt::Key::Key_F4, Qt::AltModifier, 100);
  }

}
