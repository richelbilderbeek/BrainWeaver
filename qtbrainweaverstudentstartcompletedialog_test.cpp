#include "qtbrainweaverstudentstartcompletedialog_test.h"

#include "brainweaverfile.h"
#include "qtbrainweaverstudentstartcompletedialog.h"
#include "fileio.h"

void ribi::braw::QtStudentStartCompleteDialogTest::default_construction()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
}

void ribi::braw::QtStudentStartCompleteDialogTest
  ::go_back_to_menu_is_false_at_construction()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  QVERIFY(!d.GoBackToMenu());
}

void ribi::braw::QtStudentStartCompleteDialogTest::press_escape()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::QtStudentStartCompleteDialogTest::press_nonsense()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_X);
}

void ribi::braw::QtStudentStartCompleteDialogTest::save()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  const QString filename{
    QString("test_save.") + GetFilenameExtension().c_str()
  };
  assert(!is_regular_file(filename.toStdString()));
  d.Save(filename);
  QVERIFY(is_regular_file(filename.toStdString()));
  ribi::delete_file(filename.toStdString());
  assert(!is_regular_file(filename.toStdString()));
}



void ribi::braw::QtStudentStartCompleteDialogTest
  ::start_associate()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_associate_clicked();
}

void ribi::braw::QtStudentStartCompleteDialogTest
  ::start_construct()
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_construct_clicked();
}
