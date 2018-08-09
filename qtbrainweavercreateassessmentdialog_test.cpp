#include "qtbrainweavercreateassessmentdialog_test.h"

#include <cassert>
#include <stdexcept>
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
  // CLASSIC BEHAVIOUR
  //
  //              || n_examples
  //              ||-------------------
  //             .|| 0 | 1 | 2 | 3 | >3
  // =============||===|===|===|===|===
  // n_edges |  0 || 0 | 0 | 0 | 0 | 0
  //         |  1 || 0 | 1 | 1 | 1 | 1
  //         |  2 || 1 | 2 | 2 | 2 | 2
  //         | >2 || 2 | 2 | 2 | 2 | 2

  // BEHAVIOUR SUGGESTED AT 2018-08-08 BY EMPLOYER
  //
  //              || n_examples
  //              ||-------------------
  //             .|| 0 | 1 | 2 | 3 | >3
  // =============||===|===|===|===|===
  // n_edges |  0 || 0 | 0 | 1 | 1 | 2
  //         |  1 || 0 | 1 | 1 | 2 | 2
  //         |  2 || 1 | 2 | 2 | 2 | 2
  //         | >2 || 2 | 2 | 2 | 2 | 2

  // Test for classic behaviour
  // { n_edges, n_examples }
  // First row
  QVERIFY(rating.SuggestComplexity(0, 0) == 0);
  QVERIFY(rating.SuggestComplexity(0, 1) == 0);
  QVERIFY(rating.SuggestComplexity(0, 2) == 0);
  QVERIFY(rating.SuggestComplexity(0, 3) == 0);
  QVERIFY(rating.SuggestComplexity(0, 4) == 0);
  QVERIFY(rating.SuggestComplexity(0, 5) == 0);
  // Second row
  QVERIFY(rating.SuggestComplexity(1, 0) == 0);
  QVERIFY(rating.SuggestComplexity(1, 1) == 1);
  QVERIFY(rating.SuggestComplexity(1, 2) == 1);
  QVERIFY(rating.SuggestComplexity(1, 3) == 1);
  QVERIFY(rating.SuggestComplexity(1, 4) == 1);
  QVERIFY(rating.SuggestComplexity(1, 5) == 1);
  // Third row
  QVERIFY(rating.SuggestComplexity(2, 0) == 1);
  QVERIFY(rating.SuggestComplexity(2, 1) == 2);
  QVERIFY(rating.SuggestComplexity(2, 2) == 2);
  QVERIFY(rating.SuggestComplexity(2, 3) == 2);
  QVERIFY(rating.SuggestComplexity(2, 4) == 2);
  QVERIFY(rating.SuggestComplexity(2, 5) == 2);
  // Fourth row
  QVERIFY(rating.SuggestComplexity(3, 0) == 2);
  QVERIFY(rating.SuggestComplexity(3, 1) == 2);
  QVERIFY(rating.SuggestComplexity(3, 2) == 2);
  QVERIFY(rating.SuggestComplexity(3, 3) == 2);
  QVERIFY(rating.SuggestComplexity(3, 4) == 2);
  QVERIFY(rating.SuggestComplexity(3, 5) == 2);
  // Fifth row
  QVERIFY(rating.SuggestComplexity(4, 0) == 2);
  QVERIFY(rating.SuggestComplexity(4, 1) == 2);
  QVERIFY(rating.SuggestComplexity(4, 2) == 2);
  QVERIFY(rating.SuggestComplexity(4, 3) == 2);
  QVERIFY(rating.SuggestComplexity(4, 4) == 2);
  QVERIFY(rating.SuggestComplexity(4, 5) == 2);
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
