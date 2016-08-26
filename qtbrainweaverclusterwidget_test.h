#ifndef QTBRAINWEAVERCLUSTERWIDGET_TEST_H
#define QTBRAINWEAVERCLUSTERWIDGET_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverclusterwidget_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void all_tests();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERWIDGET_TEST_H
