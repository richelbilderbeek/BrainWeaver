#include "qtbrainweaverratingdialog_test.h"

#include "brainweaverfile.h"
#include "qtbrainweaverratingdialog.h"
#include "brainweaverfilefactory.h"
#include "fileio.h"

ribi::braw::qtbrainweaverratingdialog_test
  ::qtbrainweaverratingdialog_test()
  : m_n_hits{0}
{

}

void ribi::braw::qtbrainweaverratingdialog_test::add_hit()
{
  ++m_n_hits;
}

void ribi::braw::qtbrainweaverratingdialog_test::default_construction()
{
  const File f = FileFactory().GetTests().back();
  QtRatingDialog d(f);
  d.show();
  QVERIFY(d.GetBackToMenu() || !d.GetBackToMenu()); //Always true
}

void ribi::braw::qtbrainweaverratingdialog_test::default_construction_without_nodes()
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

void ribi::braw::qtbrainweaverratingdialog_test::press_escape_should_emit_remove_me()
{
  const File file = FileFactory().Get5();
  QtRatingDialog d(file);
  const int n_hits_before{m_n_hits};
  QObject::connect(&d, SIGNAL(remove_me(QDialog * const)),this,SLOT(add_hit()));
  d.show();
  QTest::keyPress(&d, Qt::Key_Escape);
  const int n_hits_after{m_n_hits};
  QVERIFY(n_hits_before < n_hits_after);
}

void ribi::braw::qtbrainweaverratingdialog_test::save()
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
