#ifndef QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_TEST_H
#define QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtCreateAssessmentDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void CloseOnEscape() const noexcept;
  void Construction() const noexcept;
  void HasCorrectDefaultRating() const noexcept;
  void QuickSaveFirstTimeOpensDialog() const noexcept;
  void QuickSaveSecondTimeSavesFast() const noexcept;
  void Save() const noexcept;
  void SetAndGetQuestionIsSymmetric() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_TEST_H
