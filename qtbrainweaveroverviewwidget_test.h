#ifndef QTBRAINWEAVEROVERVIEWWIDGET_TEST_H
#define QTBRAINWEAVEROVERVIEWWIDGET_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtOverviewWidgetTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construction();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVEROVERVIEWWIDGET_TEST_H
