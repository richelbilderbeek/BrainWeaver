#include "qtbrainweavercreateassessmentcompletedialog_test.h"

#include <cassert>
#include <stdexcept>
#include "fileio.h"

#include "brainweaverfile.h"
#include "qtbrainweavercreateassessmentcompletedialog.h"

void ribi::braw::qtbrainweavercreateassessmentcompletedialog_test::close_on_escape()
{
  QtCreateAssessmentCompleteDialog d;
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::qtbrainweavercreateassessmentcompletedialog_test::default_construction()
{
  QtCreateAssessmentCompleteDialog d;
  d.show();
}

void ribi::braw::qtbrainweavercreateassessmentcompletedialog_test::save()
{
  QtCreateAssessmentCompleteDialog d;
  d.SetQuestion("A question");
  const std::string filename{"test_save." + GetFilenameExtension()};
  assert(!is_regular_file(filename));
  d.Save(filename);
  QVERIFY(is_regular_file(filename));
  ribi::delete_file(filename);
  assert(!is_regular_file(filename));
}


void ribi::braw::qtbrainweavercreateassessmentcompletedialog_test::save_with_incorrect_extension()
{
  QtCreateAssessmentCompleteDialog d;
  d.SetQuestion("A question");
  const std::string filename{"save_with_incorrect_extension"};
  try
  {
    d.Save(filename); //Should throw
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument&)
  {
    QVERIFY("Should get here");
  }
}


void ribi::braw::qtbrainweavercreateassessmentcompletedialog_test::set_and_get_question()
{
  QtCreateAssessmentCompleteDialog d;
  const std::string s{"What is good question?"};
  d.SetQuestion(s);
  QVERIFY(d.GetQuestion() == s);
}
