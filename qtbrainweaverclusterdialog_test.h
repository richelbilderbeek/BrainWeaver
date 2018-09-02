#ifndef QTBRAINWEAVERCLUSTERDIALOG_TEST_H
#define QTBRAINWEAVERCLUSTERDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtClusterDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void ButtonAddClickedNothingToAdd() const noexcept;
  void ButtonAddClickedSomethingToAdd() const noexcept;
  void ButtonNextClickedNoConceptMap() const noexcept;
  void ButtonNextClickedWithConceptMap() const noexcept;
  void ClusterDialogEnabledIfNoConceptMap() const noexcept;
  void ClusterDialogDisabledIfNodesInConceptMap() const noexcept;
  void DefaultConstruct() const noexcept;
  void EnableButtonDependingOnFile() const noexcept;
  void GetWidget() const noexcept;
  void PressEscape() const noexcept;
  void PressSomething() const noexcept;
  void QuickSaveFirstTimeOpensDialog() const noexcept;
  void QuickSaveSecondTimeSavesFast() const noexcept;
  void Save() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERDIALOG_TEST_H
