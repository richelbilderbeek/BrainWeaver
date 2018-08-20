#ifndef QTBRAINWEAVERRATECONCEPTMAPDIALOG_TEST_H
#define QTBRAINWEAVERRATECONCEPTMAPDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtRateConceptMapDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void ButtonNextClicked() const noexcept;
  void ChangeEvents() const noexcept;
  void CloseOnEscape() const noexcept;
  void FileMustMatchGetFile() const noexcept;
  void QuickSaveFirstTimeOpensDialog() const noexcept;
  void QuickSaveSecondTimeSavesFast() const noexcept;
  void Save() const noexcept;
  void WidgetIsInitialized() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERRATECONCEPTMAPDIALOG_TEST_H
