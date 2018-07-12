#include "qtbrainweaverdisplay_test.h"

#include <memory>
#include <QTableWidget>
#include "qtbrainweaverdisplay.h"
#include "brainweaverfile.h"
#include "brainweaverfilefactory.h"

void ribi::braw::qtbrainweaverdisplay_test::display_rated_concepts()
{
  File f = FileFactory().GetTests().back();
  const QtDisplay d;
  std::unique_ptr<QTableWidget> widget(new QTableWidget);
  widget->setRowCount(4);
  widget->setColumnCount(3);
  widget->show();
  d.DisplayRatedConcepts(f, widget.get());
  QVERIFY("Should get here");
}

void ribi::braw::qtbrainweaverdisplay_test::display_rated_concepts_without_center_node()
{
  File f;
  const QtDisplay d;
  std::unique_ptr<QTableWidget> widget(new QTableWidget);
  widget->setRowCount(4);
  widget->setColumnCount(3);
  widget->show();
  try
  {
    d.DisplayRatedConcepts(f, widget.get());
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument& e)
  {
    const std::string expected_message{
      "DisplayRatedConcepts: must have at least one node"
    };
    QVERIFY(std::string(e.what()) == expected_message);
    QVERIFY("Should get here");
  }
}
