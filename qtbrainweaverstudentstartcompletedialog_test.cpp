#include "qtbrainweaverstudentstartcompletedialog_test.h"

#include "brainweaverfile.h"
#include "brainweaverfilefactory.h"
#include "qtbrainweaverstudentstartcompletedialog.h"
#include "qtbrainweaverfiledialog.h"
#include "fileio.h"

void ribi::braw::QtStudentStartCompleteDialogTest
  ::DefaultConstruction() const noexcept
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
}

void ribi::braw::QtStudentStartCompleteDialogTest
  ::GoBackToMenuIsFalseAtConstruction() const noexcept
{
  File f;
  QtStudentStartCompleteDialog d(f);
  QVERIFY(!d.GoBackToMenu());
}

void ribi::braw::QtStudentStartCompleteDialogTest::PressEscape() const noexcept
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::QtStudentStartCompleteDialogTest::PressNonsense() const noexcept
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_X);
}

void ribi::braw::QtStudentStartCompleteDialogTest::QuickSaveFirstTimeOpensDialog() const noexcept
{
  const File file = FileFactory().GetUnrated();
  QtStudentStartCompleteDialog d(file);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
}


void ribi::braw::QtStudentStartCompleteDialogTest::QuickSaveSecondTimeSavesFast() const noexcept
{
  const File file = FileFactory().GetUnrated();
  QtStudentStartCompleteDialog d(file);
  const QString filename{"tmp.cmp"};
  QtFileDialog::m_last_file = filename;
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
  QVERIFY(QFile::exists(filename));
  QFile::remove(filename);
}

void ribi::braw::QtStudentStartCompleteDialogTest::Save() const noexcept
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
  ::StartAssociate() const noexcept
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_associate_clicked();
}

void ribi::braw::QtStudentStartCompleteDialogTest::StartConstruct() const noexcept
{
  File f;
  QtStudentStartCompleteDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_construct_clicked();
}

