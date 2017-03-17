#include "qtbrainweaverdisplay_test.h"

#include <memory>
#include <QTableWidget>
#include "qtbrainweaverdisplay.h"
#include "brainweaverfile.h"
#include "brainweaverfilefactory.h"

void ribi::braw::qtbrainweaverdisplay_test::display_examples()
{
  File f = FileFactory().Get5();
  const QtDisplay d;
  std::unique_ptr<QTableWidget> widget(new QTableWidget);
  widget->setColumnCount(2);
  widget->setRowCount(7);
  widget->show();
  d.DisplayExamples(f, widget.get());
  QVERIFY("Should get here");
}

void ribi::braw::qtbrainweaverdisplay_test::display_misc_values()
{
  const QtDisplay d;
  std::unique_ptr<QTableWidget> widget(new QTableWidget);
  widget->setRowCount(4);
  widget->setColumnCount(3);
  widget->show();
  File f = FileFactory().Get5();
  d.DisplayMiscValues(f, widget.get());
  QVERIFY("Should get here");
}

void ribi::braw::qtbrainweaverdisplay_test::display_misc_values_without_center_node()
{

  const QtDisplay d;
  std::unique_ptr<QTableWidget> widget(new QTableWidget);
  widget->setRowCount(4);
  widget->setColumnCount(3);
  widget->show();
  try
  {
    File f; //This file does not have a center node: it is empty
    d.DisplayMiscValues(f, widget.get());
    QVERIFY(!"Should not get here");
  }
  catch (std::logic_error& e)
  {
    const std::string expected_message{
      "FindCenterNode: Cannot find the one center node, as there are 0"
    };
    QVERIFY(std::string(e.what()) == expected_message);
    QVERIFY("Should get here");
  }
}

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

void ribi::braw::qtbrainweaverdisplay_test::display_values()
{

  File f = FileFactory().GetTests().back();
  const QtDisplay d;
  std::unique_ptr<QTableWidget> widget(new QTableWidget);
  widget->show();
  widget->setRowCount(4);
  widget->setColumnCount(3);
  d.DisplayValues(f, widget.get());
  QVERIFY("Should get here");
}

void ribi::braw::qtbrainweaverdisplay_test::display_values_without_nodes()
{
  File f;
  const QtDisplay d;
  std::unique_ptr<QTableWidget> widget(new QTableWidget);
  widget->show();
  try
  {
    d.DisplayValues(f, widget.get());
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument& e)
  {
    const std::string expected_message = "DisplayValues: must have at least one node";
    QVERIFY(std::string(e.what()) == expected_message);
    QVERIFY("Should get here");
  }
}

