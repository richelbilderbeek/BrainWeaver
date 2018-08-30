#include "qtbrainweaverratingdialog_test.h"

#include "brainweaverfile.h"
#include "brainweaverfilefactory.h"
#include "fileio.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaverratingdialog.h"
#include "ui_qtbrainweaverratingdialog.h"

void ribi::braw::QtRatingDialogTest::Construction() const noexcept
{
  const File f = FileFactory().GetTests().back();
  QtRatingDialog d(f);
  d.show();
}

void ribi::braw::QtRatingDialogTest::ConstructionWithoutNodes() const noexcept
{
  const File f;
  try
  {
    QtRatingDialog d(f);
    d.show();
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument& e)
  {
    const std::string expected_message = "QtRatingDialog: must have at least one node";
    QVERIFY(std::string(e.what()) == expected_message);
    QVERIFY("Should get here");
  }
}

void ribi::braw::QtRatingDialogTest::EditName() const noexcept
{
  const File file = FileFactory().Get5();
  QtRatingDialog d(file);
  d.on_edit_name_textEdited("");
  d.on_edit_name_textEdited("Something else");
  d.on_edit_name_textEdited("");
  d.on_edit_name_textEdited("Something else again");
  d.ui->edit_name->setText("");
  d.ui->edit_name->setText("Other");
  d.ui->edit_name->setText("");
  d.ui->edit_name->setText("Another other");
}

void ribi::braw::QtRatingDialogTest::PressEscapeClosesDialog() const noexcept
{
  const File file = FileFactory().Get5();
  QtRatingDialog d(file);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
  QVERIFY(d.isHidden());
}

void ribi::braw::QtRatingDialogTest::Print() const noexcept
{
  const File file = FileFactory().Get5();
  QtRatingDialog d(file);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_print_clicked();
}

void ribi::braw::QtRatingDialogTest::QuickSaveFirstTimeOpensDialog() const noexcept
{
  const File file = FileFactory().Get5();
  QtRatingDialog d(file);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  QtFileDialog::m_last_file = "";
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
}


void ribi::braw::QtRatingDialogTest::QuickSaveSecondTimeSavesFast() const noexcept
{
  const File file = FileFactory().Get5();
  QtRatingDialog d(file);
  const QString filename{"tmp.cmp"};
  QtFileDialog::m_last_file = filename;
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
  QVERIFY(QFile::exists(filename));
  QFile::remove(filename);
}

void ribi::braw::QtRatingDialogTest::Save() const noexcept
{
  const std::string filename{
    "qtbrainweaverratingdialog_test_save.cmp"
  };
  if (ribi::is_regular_file(filename)) { ribi::delete_file(filename); }
  assert(!ribi::is_regular_file(filename));

  const File file = FileFactory().Get5();
  QtRatingDialog d(file);
  d.show();
  d.Save(filename);
  QVERIFY(ribi::is_regular_file(filename));

}
