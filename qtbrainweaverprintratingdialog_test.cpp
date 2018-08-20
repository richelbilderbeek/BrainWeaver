#include "qtbrainweaverprintratingdialog_test.h"
#include "qtbrainweaverprintratingdialog.h"

#include "brainweaverfile.h"
#include "brainweaverfilefactory.h"
#include "fileio.h"

void ribi::braw::QtPrintRatingDialogTest::default_construction()
{
  const File f = FileFactory().GetTests().back();
  ribi::braw::QtPrintRatingDialog d(f);
  d.show();
}

void ribi::braw::QtPrintRatingDialogTest::default_construction_without_nodes()
{
  const File f;
  try
  {
    ribi::braw::QtPrintRatingDialog d(f);
    d.show();
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument& e)
  {
    const std::string expected_message{
      "Need at least one non-focal node to calculate experimental complexity"
    };
    QVERIFY(std::string(e.what()) == expected_message);
    QVERIFY("Should get here");
  }
}

void ribi::braw::QtPrintRatingDialogTest::print_should_produce_file()
{
  const auto file = FileFactory().Get3();
  QtPrintRatingDialog d(file);
  d.show();
  const std::string filename{
    "qtbrainweaverprintconceptmapdialog_test.pdf"
  };
  if (ribi::is_regular_file(filename)) { ribi::delete_file(filename); }
  QVERIFY(!ribi::is_regular_file(filename));
  d.Print(filename);
  QVERIFY(ribi::is_regular_file(filename));

  //Cleanup
  if (ribi::is_regular_file(filename)) { ribi::delete_file(filename); }
  assert(!ribi::is_regular_file(filename));

}
