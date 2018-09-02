#ifndef QTBRAINWEAVERMENUDIALOG_TEST_H
#define QTBRAINWEAVERMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtMenuDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void PressAllKeys() const noexcept;
  void PressAllKeysFromMemberFunctions() const noexcept;

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERMENUDIALOG_TEST_H
