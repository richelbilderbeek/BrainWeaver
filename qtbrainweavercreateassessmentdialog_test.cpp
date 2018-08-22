#include "qtbrainweavercreateassessmentdialog_test.h"

#include <cassert>
#include <stdexcept>
#include <iostream>
#include "fileio.h"

#include "brainweaverfile.h"
#include "conceptmaprating.h"
#include "qtbrainweavercreateassessmentdialog.h"
#include "qtbrainweaverfiledialog.h"

void ribi::braw::QtCreateAssessmentDialogTest::CloseOnEscape() const noexcept
{
  QtCreateAssessmentDialog d;
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
  QVERIFY(d.isHidden());
}

void ribi::braw::QtCreateAssessmentDialogTest::Construction() const noexcept
{
  QtCreateAssessmentDialog d;
  d.show();
}

void ribi::braw::QtCreateAssessmentDialogTest
  ::HasCorrectDefaultRating() const noexcept
{
  const QtCreateAssessmentDialog d;
  const ribi::cmap::Rating rating = d.GetRating();
  QVERIFY(rating == ribi::cmap::CreateDefaultRating());
}

void ribi::braw::QtCreateAssessmentDialogTest::QuickSaveFirstTimeOpensDialog() const noexcept
{
  QtCreateAssessmentDialog d;
  d.show();
  QTimer::singleShot(100, qApp, SLOT(closeAllWindows()));
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
}


void ribi::braw::QtCreateAssessmentDialogTest::QuickSaveSecondTimeSavesFast() const noexcept
{
  QtCreateAssessmentDialog d;
  const QString filename{"tmp.cmp"};
  QtFileDialog::m_last_file = filename;
  QTest::keyPress(&d, Qt::Key_S, Qt::ControlModifier);
  QVERIFY(QFile::exists(filename));
  QFile::remove(filename);
}

void ribi::braw::QtCreateAssessmentDialogTest::Save() const noexcept
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


void ribi::braw::QtCreateAssessmentDialogTest::SetAndGetQuestionIsSymmetric() const noexcept
{
  QtCreateAssessmentDialog d;
  const std::string s{"What is good question?"};
  d.SetQuestion(s);
  QVERIFY(d.GetQuestion() == s);
}
