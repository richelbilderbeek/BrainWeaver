#include "qtbrainweaverassessormenudialog_test.h"

#include "brainweaverfilefactory.h"
#include "fileio.h"
#include "qtbrainweaverassessormenudialog.h"
#include "qtbrainweaverfiledialog.h"

void ribi::braw::QtAssessorMenuDialogTest::Assess() const noexcept
{
  const std::string filename{
    "assess.cmp"
  };

  if (ribi::is_regular_file(filename))
  {
    ribi::delete_file(filename);
  }

  File f = FileFactory().Get3();
  f.Save(filename);
  assert(ribi::is_regular_file(filename));

  QtAssessorMenuDialog d;
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.Assess(filename);
  ribi::delete_file(filename);
  assert(!ribi::is_regular_file(filename));
}

void ribi::braw::QtAssessorMenuDialogTest::ClickAboutButtonShowsAboutDialog() const noexcept
{
  QtAssessorMenuDialog d;
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_about_clicked();
}

void ribi::braw::QtAssessorMenuDialogTest::ClickCreateButtonStartsAssessment() const noexcept
{
  QtAssessorMenuDialog d;
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_create_assessment_clicked();
}

void ribi::braw::QtAssessorMenuDialogTest::Construction() const noexcept
{
  QtAssessorMenuDialog d;
  d.show();
}

void ribi::braw::QtAssessorMenuDialogTest::PressEscapeClosesDialog() const noexcept
{
  QtAssessorMenuDialog d;
  d.show();
  assert(!d.isHidden());
  QTest::keyClick(&d, Qt::Key_Escape);
  QVERIFY(d.isHidden());
}

void ribi::braw::QtAssessorMenuDialogTest::QuickSaveFirstTimeOpensDialog() const noexcept
{
  QtAssessorMenuDialog d;
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
}

void ribi::braw::QtAssessorMenuDialogTest::QuickSaveSecondTimeSavesFast() const noexcept
{
  QtAssessorMenuDialog d;
  const QString filename{"tmp.cmp"};
  QtFileDialog::m_last_file = filename;
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
  QVERIFY(QFile::exists(filename));
  QFile::remove(filename);
}
