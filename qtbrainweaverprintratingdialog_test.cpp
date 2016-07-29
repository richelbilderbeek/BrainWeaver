#include "qtbrainweaverprintratingdialog_test.h"
#include "qtbrainweaverprintratingdialog.h"

#include "brainweaverfile.h"
#include "brainweaverfilefactory.h"

void ribi::braw::qtbrainweaverprintratingdialog_test::default_construction()
{
  const File f = FileFactory().GetTests().back();
  ribi::braw::QtPrintRatingDialog d(f);
  d.show();
  QVERIFY(d.GetTableConcepts());
  QVERIFY(d.GetTableExamples());
  QVERIFY(d.GetTableMiscValues());
  QVERIFY(d.GetTableValues());
  QVERIFY(!d.GetVersion().empty());
  QVERIFY(!d.GetVersionHistory().empty());
}

void ribi::braw::qtbrainweaverprintratingdialog_test::default_construction_without_nodes()
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
    const std::string expected_message = "QtPrintRatingDialog: must have at least one node";
    QVERIFY(std::string(e.what()) == expected_message);
    QVERIFY("Should get here");
  }
}
