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

void ribi::braw::qtbrainweaverstudentmenudialog_test::click_button_quit()
{
  File f;
  QtStudentMenuDialog d(f);
  d.show();
  d.on_button_quit_clicked();
}

void ribi::braw::qtbrainweaverstudentmenudialog_test::click_button_start()
{
  File f;
  f.SetStudentName("John Doe");
  QtStudentMenuDialog d(f);
  d.show();
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
  const std::string filename{"test_save." + GetFilenameExtension()};
  assert(!is_regular_file(filename));
  d.Save(filename);
  QVERIFY(is_regular_file(filename));
  ribi::delete_file(filename);
  assert(!is_regular_file(filename));
}


void ribi::braw::qtbrainweaverstudentmenudialog_test::save_with_incorrect_extension()
{
  File f;
  QtStudentMenuDialog d(f);
  d.SetName("John Doe");
  const std::string filename{"save_with_incorrect_extension"};
  try
  {
    d.Save(filename); //Should throw
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument&)
  {
    QVERIFY("Should get here");
  }
}

void ribi::braw::qtbrainweaverstudentmenudialog_test::set_and_get_name()
{
  File f;
  QtStudentMenuDialog d(f);
  const std::string name{"Elenore Aderman"};
  QVERIFY(d.GetName() != name);
  d.SetName(name);
  QVERIFY(d.GetName() == name);

}
