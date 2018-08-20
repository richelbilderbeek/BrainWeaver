#include "qtbrainweaverratingdialog_test.h"
#include "ui_qtbrainweaverratingdialog.h"

#include "brainweaverfile.h"
#include "qtbrainweaverratingdialog.h"
#include "brainweaverfilefactory.h"
#include "fileio.h"

ribi::braw::QtRatingDialogTest
  ::QtRatingDialogTest()
  : m_n_hits{0}
{

}

void ribi::braw::QtRatingDialogTest::add_hit()
{
  ++m_n_hits;
}

void ribi::braw::QtRatingDialogTest::default_construction()
{
  const File f = FileFactory().GetTests().back();
  QtRatingDialog d(f);
  d.show();
}

void ribi::braw::QtRatingDialogTest::default_construction_without_nodes()
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

void ribi::braw::QtRatingDialogTest::edit_name()
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

void ribi::braw::QtRatingDialogTest::print()
{
  const File file = FileFactory().Get5();
  QtRatingDialog d(file);
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_print_clicked();
}

void ribi::braw::QtRatingDialogTest::save()
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
