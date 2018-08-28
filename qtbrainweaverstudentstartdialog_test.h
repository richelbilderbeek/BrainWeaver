#ifndef QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_TEST_H
#define QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtStudentStartDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void DefaultConstruction() const noexcept;
  void GoBackToMenuIsFalseAtConstruction() const noexcept;
  void PressEscape() const noexcept;
  void PressNonsense() const noexcept;
  void QuickSaveFirstTimeOpensDialog() const noexcept;
  void QuickSaveSecondTimeSavesFast() const noexcept;
  void Save() const noexcept;
  void StartAssociate() const noexcept;
  void StartConstruct() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_TEST_H
