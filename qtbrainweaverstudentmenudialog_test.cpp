#include "qtbrainweaverstudentmenudialog_test.h"

#include <cassert>

#include "brainweaverfile.h"
#include "qtbrainweaverstudentmenudialog.h"
#include "fileio.h"

void ribi::braw::qtbrainweaverstudentmenudialog_test::click_button_about_clicked()
{
  //Bad idea: a window will pop up


  //File f;
  //QtStudentMenuDialog d(f);
  //d.show();
  //d.on_button_about_clicked();
}

void ribi::braw::qtbrainweaverstudentmenudialog_test::click_button_start()
{
  File f;
  f.SetStudentName("John Doe");
  QtStudentMenuDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_clicked();
}

void ribi::braw::qtbrainweaverstudentmenudialog_test::default_construction()
{
  File f;
  QtStudentMenuDialog d(f);
  d.show();
}

void ribi::braw::qtbrainweaverstudentmenudialog_test::press_escape()
{
  File f;
  QtStudentMenuDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::qtbrainweaverstudentmenudialog_test::save()
{
  File f;
  QtStudentMenuDialog d(f);
  d.SetName("Jane Doe");
  const QString filename{QString("test_save.") + GetFilenameExtension().c_str()};
  assert(!is_regular_file(filename.toStdString()));
  d.Save(filename);
  QVERIFY(is_regular_file(filename.toStdString()));
  ribi::delete_file(filename.toStdString());
  assert(!is_regular_file(filename.toStdString()));
}

void ribi::braw::qtbrainweaverstudentmenudialog_test::set_and_get_name()
{
  File f;
  QtStudentMenuDialog d(f);
  const QString name{"Elenore Aderman"};
  QVERIFY(d.GetName() != name);
  d.SetName(name);
  QVERIFY(d.GetName() == name);

}
