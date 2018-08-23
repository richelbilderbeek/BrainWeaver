#ifndef QTBRAINWEAVERFILEDIALOG_TEST_H
#define QTBRAINWEAVERFILEDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtFileDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void DefaultConstruction() const noexcept;
  void OpenDialogSaysKijkIn() const noexcept;
  void OpenDialogSaysOpen() const noexcept;
  void OpenDialogSaysBestanden() const noexcept;
  void OpenDialogShouldSaySoortBestanden() const noexcept;
  void SaveDialogShouldSayKijkIn() const noexcept; //123
  void SaveDialogShouldSaySlaOp() const noexcept; //123
  void SaveDialogShouldSayBestanden() const noexcept; //126
  void SaveDialogShouldSaySoortBestanden() const noexcept; //126
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERFILEDIALOG_TEST_H
