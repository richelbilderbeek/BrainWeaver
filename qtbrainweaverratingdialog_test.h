#ifndef QTBRAINWEAVERRATINGDIALOG_TEST_H
#define QTBRAINWEAVERRATINGDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtRatingDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void Construction() const noexcept;
  void ConstructionWithoutNodes() const noexcept;
  void EditName() const noexcept;
  void Print() const noexcept;
  void PressEscapeClosesDialog() const noexcept;
  void QuickSaveFirstTimeOpensDialog() const noexcept;
  void QuickSaveSecondTimeSavesFast() const noexcept;
  void Save() const noexcept;

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERRATINGDIALOG_TEST_H
