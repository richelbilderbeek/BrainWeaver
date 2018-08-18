#ifndef QTBRAINWEAVEROVERVIEWDIALOG_TEST_H
#define QTBRAINWEAVEROVERVIEWDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtBrainWeaverOverviewDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void CloseOnEscape();
  void Construction();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVEROVERVIEWDIALOG_TEST_H
