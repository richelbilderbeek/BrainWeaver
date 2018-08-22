#ifndef QTBRAINWEAVERASSESSORMENUDIALOG_TEST_H
#define QTBRAINWEAVERASSESSORMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtAssessorMenuDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void Assess() const noexcept;
  void ClickAboutButtonShowsAboutDialog() const noexcept;
  void ClickAssessButtonStartsRating() const noexcept;
  void ClickCreateButtonStartsAssessment() const noexcept;
  void Construction() const noexcept;
  void PressEscapeClosesDialog() const noexcept;
  void QuickSaveFirstTimeOpensDialog() const noexcept;
  void QuickSaveSecondTimeSavesFast() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERASSESSORMENUDIALOG_TEST_H
