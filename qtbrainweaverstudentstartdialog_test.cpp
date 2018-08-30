#include "qtbrainweaverstudentstartdialog_test.h"

#include "brainweaverfile.h"
#include "brainweaverfilefactory.h"
#include "qtbrainweaverstudentstartdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "fileio.h"

void ribi::braw::QtStudentStartDialogTest
  ::DefaultConstruction() const noexcept
{
  File f;
  QtStudentStartDialog d(f);
  d.show();
}

void ribi::braw::QtStudentStartDialogTest
  ::GoBackToMenuIsFalseAtConstruction() const noexcept
{
  File f;
  QtStudentStartDialog d(f);
  QVERIFY(!d.GoBackToMenu());
}

void ribi::braw::QtStudentStartDialogTest::PressEscape() const noexcept
{
  File f;
  QtStudentStartDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::QtStudentStartDialogTest::PressNonsense() const noexcept
{
  File f;
  QtStudentStartDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_X);
}

void ribi::braw::QtStudentStartDialogTest::QuickSaveFirstTimeOpensDialog() const noexcept
{
  const File file = FileFactory().GetUnrated();
  QtStudentStartDialog d(file);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  QtFileDialog::m_last_file = "";
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
}


void ribi::braw::QtStudentStartDialogTest::QuickSaveSecondTimeSavesFast() const noexcept
{
  const File file = FileFactory().GetUnrated();
  QtStudentStartDialog d(file);
  const QString filename{"tmp.cmp"};
  QtFileDialog::m_last_file = filename;
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
  QVERIFY(QFile::exists(filename));
  QFile::remove(filename);
}

void ribi::braw::QtStudentStartDialogTest::Save() const noexcept
{
  File f;
  QtStudentStartDialog d(f);
  const QString filename{
    QString("test_save.") + GetFilenameExtension().c_str()
  };
  assert(!is_regular_file(filename.toStdString()));
  d.Save(filename);
  QVERIFY(is_regular_file(filename.toStdString()));
  ribi::delete_file(filename.toStdString());
  assert(!is_regular_file(filename.toStdString()));
}



void ribi::braw::QtStudentStartDialogTest
  ::StartAssociate() const noexcept
{
  File f;
  QtStudentStartDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_associate_clicked();
}

void ribi::braw::QtStudentStartDialogTest::StartConstruct() const noexcept
{
  File f;
  QtStudentStartDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_construct_clicked();
}

