#include "qtbrainweavercreateassessmentdialog_test.h"

#include <cassert>
#include <stdexcept>
#include <iostream>
#include "fileio.h"

#include "brainweaverfile.h"
#include "conceptmaprating.h"
#include "qtbrainweavercreateassessmentdialog.h"

void ribi::braw::QtCreateAssessmentDialogTest::CloseOnEscape()
{
  QtCreateAssessmentDialog d;
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::QtCreateAssessmentDialogTest::default_construction()
{
  QtCreateAssessmentDialog d;
  d.show();
}

void ribi::braw::QtCreateAssessmentDialogTest
  ::has_correct_default_rating()
{
  const QtCreateAssessmentDialog d;
  const ribi::cmap::Rating rating = d.GetRating();
  QVERIFY(rating == ribi::cmap::CreateDefaultRating());
}

void ribi::braw::QtCreateAssessmentDialogTest::save()
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


void ribi::braw::QtCreateAssessmentDialogTest::set_and_get_question()
{
  QtCreateAssessmentDialog d;
  const std::string s{"What is good question?"};
  d.SetQuestion(s);
  QVERIFY(d.GetQuestion() == s);
}
