#include "qtbrainweavercreateassessmentdialog_test.h"

#include <cassert>
#include <stdexcept>
#include <iostream>
#include "fileio.h"

#include "brainweaverfile.h"
#include "conceptmaprating.h"
#include "qtbrainweavercreateassessmentdialog.h"

void ribi::braw::qtbrainweavercreateassessmentdialog_test::close_on_escape()
{
  QtCreateAssessmentDialog d;
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::qtbrainweavercreateassessmentdialog_test::default_construction()
{
  QtCreateAssessmentDialog d;
  d.show();
}

void ribi::braw::qtbrainweavercreateassessmentdialog_test
  ::has_correct_default_rating()
{
  const QtCreateAssessmentDialog d;
  const ribi::cmap::Rating rating = d.GetRating();
  QVERIFY(rating == ribi::cmap::CreateDefaultRating());
}

void ribi::braw::qtbrainweavercreateassessmentdialog_test::save()
{
  QtCreateAssessmentDialog d;
  d.SetQuestion("A question");
  const std::string filename{"test_save." + GetFilenameExtension()};
  assert(!is_regular_file(filename));
  d.Save(filename);
  QVERIFY(is_regular_file(filename));
  ribi::delete_file(filename);
  assert(!is_regular_file(filename));
}


void ribi::braw::qtbrainweavercreateassessmentdialog_test::set_and_get_question()
{
  QtCreateAssessmentDialog d;
  const std::string s{"What is good question?"};
  d.SetQuestion(s);
  QVERIFY(d.GetQuestion() == s);
}
