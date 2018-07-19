#include "qtbrainweaverstudentstartcompletedialog_test.h"

#include "brainweaverfile.h"
#include "qtbrainweaverstudentstartcompletedialog.h"
#include "fileio.h"

void ribi::braw::qtbrainweaverstudentstartcompletedialog_test::default_construction()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
}

void ribi::braw::qtbrainweaverstudentstartcompletedialog_test
  ::go_back_to_menu_is_false_at_construction()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  QVERIFY(!d.GoBackToMenu());
}

void ribi::braw::qtbrainweaverstudentstartcompletedialog_test::press_escape()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::qtbrainweaverstudentstartcompletedialog_test::press_nonsense()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_X);
}

void ribi::braw::qtbrainweaverstudentstartcompletedialog_test::save()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  const std::string filename{"test_save." + GetFilenameExtension()};
  assert(!is_regular_file(filename));
  d.Save(filename);
  QVERIFY(is_regular_file(filename));
  ribi::delete_file(filename);
  assert(!is_regular_file(filename));
}



void ribi::braw::qtbrainweaverstudentstartcompletedialog_test
  ::start_associate()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_associate_clicked();
}

void ribi::braw::qtbrainweaverstudentstartcompletedialog_test
  ::start_construct()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_construct_clicked();
}
