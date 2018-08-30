#include "qtbrainweaverstudentmenudialog_test.h"

#include <cassert>

#include "brainweaverfile.h"
#include "qtbrainweaverstudentmenudialog.h"
#include "fileio.h"
#include "qtbrainweaverfiledialog.h"

void ribi::braw::QtStudentMenuDialogTest::ClickAboutButton()
{
  File f;
  QtStudentMenuDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_about_clicked();
}

void ribi::braw::QtStudentMenuDialogTest::ClickStartButton()
{
  File f;
  f.SetStudentName("John Doe");
  QtStudentMenuDialog d(f);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_start_clicked();
}

void ribi::braw::QtStudentMenuDialogTest::DefaultConstruction()
{
  const File f;
  QtStudentMenuDialog d(f);
  d.show();
  QVERIFY(f == d.GetFile());
}

void ribi::braw::QtStudentMenuDialogTest::QuickSaveFirstTimeOpensDialog()
{
  File f;
  QtStudentMenuDialog d(f);
  d.show();
  d.SetName("Jane Doe");
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  QtFileDialog::m_last_file = "";
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
}

void ribi::braw::QtStudentMenuDialogTest::QuickSaveSecondTimeSavesFast()
{
  File f;
  QtStudentMenuDialog d(f);
  d.SetName("Jane Doe");
  const QString filename{"tmp.cmp"};
  QtFileDialog::m_last_file = filename;
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
  QVERIFY(QFile::exists(filename));
  QFile::remove(filename);
}

void ribi::braw::QtStudentMenuDialogTest::PressEscapeClosesDialog()
{
  File f;
  QtStudentMenuDialog d(f);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
  QVERIFY(d.isHidden());
}

void ribi::braw::QtStudentMenuDialogTest::Save()
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

void ribi::braw::QtStudentMenuDialogTest::SetAndGetName()
{
  File f;
  QtStudentMenuDialog d(f);
  const QString name{"Elenore Aderman"};
  QVERIFY(d.GetName() != name);
  d.SetName(name);
  QVERIFY(d.GetName() == name);

}
