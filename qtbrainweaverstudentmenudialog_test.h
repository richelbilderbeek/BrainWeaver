#ifndef QTBRAINWEAVERSTUDENTMENUDIALOG_TEST_H
#define QTBRAINWEAVERSTUDENTMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtBrainWeaverStudentMenuDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void ClickAboutButton();
  void ClickStartButton();
  void DefaultConstruction();
  void QuickSaveFirstTimeOpensDialog();
  void QuickSaveSecondTimeSavesFast();
  void PressEscape();
  void Save();
  void SetAndGetName();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTMENUDIALOG_TEST_H
