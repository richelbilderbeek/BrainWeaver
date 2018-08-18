#ifndef QTBRAINWEAVERMENUDIALOG_TEST_H
#define QTBRAINWEAVERMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtBrainWeaverMenuDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void Construction();
  void PressAllKeys();

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERMENUDIALOG_TEST_H
