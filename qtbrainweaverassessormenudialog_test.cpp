#include "qtbrainweaverassessormenudialog_test.h"
#include "qtbrainweaverassessormenudialog.h"

void ribi::braw::qtbrainweaverassessormenudialog_test::click_button_about_clicked()
{
  QtAssessorMenuDialog d;
  d.show();
  d.on_button_about_clicked();
}

void ribi::braw::qtbrainweaverassessormenudialog_test::click_button_assess_result()
{
  //Bad idea: will open up a save dialog

  //QtAssessorMenuDialog d;
  //d.show();
  //d.on_button_assess_result_clicked();
}

void ribi::braw::qtbrainweaverassessormenudialog_test::click_button_create_assessment()
{
  QtAssessorMenuDialog d;
  d.show();
  d.on_button_create_assessment_clicked();

}

void ribi::braw::qtbrainweaverassessormenudialog_test::click_button_quit()
{
  QtAssessorMenuDialog d;
  d.show();
  d.on_button_quit_clicked();
}

void ribi::braw::qtbrainweaverassessormenudialog_test::default_construction()
{
  QtAssessorMenuDialog d;
  d.show();
}

void ribi::braw::qtbrainweaverassessormenudialog_test::press_escape()
{
  QtAssessorMenuDialog d;
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

