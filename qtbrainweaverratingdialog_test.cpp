#include "qtbrainweaverratingdialog_test.h"

#include "brainweaverfile.h"
#include "qtbrainweaverratingdialog.h"
#include "brainweaverfilefactory.h"

void ribi::braw::qtbrainweaverratingdialog_test::default_construction()
{
  const File f = FileFactory().GetTests().back();
  ribi::braw::QtRatingDialog d(f);
  d.show();
  QVERIFY(!d.GetVersion().empty());
  QVERIFY(!d.GetVersionHistory().empty());
}

void ribi::braw::qtbrainweaverratingdialog_test::default_construction_without_nodes()
{
  const File f;
  try
  {
    ribi::braw::QtRatingDialog d(f);
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
