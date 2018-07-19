#include "qtbrainweaverassessormenudialog_test.h"

#include "fileio.h"
#include "brainweaverfilefactory.h"
#include "qtbrainweaverassessormenudialog.h"

void ribi::braw::qtbrainweaverassessormenudialog_test::assess()
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

void ribi::braw::qtbrainweaverassessormenudialog_test::click_button_about_clicked()
{
  QtAssessorMenuDialog d;
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_about_clicked();
}

void ribi::braw::qtbrainweaverassessormenudialog_test::click_button_create_assessment()
{
  QtAssessorMenuDialog d;
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  d.on_button_create_assessment_clicked();
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

