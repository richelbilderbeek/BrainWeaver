#ifndef QTBRAINWEAVERCLUSTERTREEWIDGETITEM_TEST_H
#define QTBRAINWEAVERCLUSTERTREEWIDGETITEM_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtClusterTreeWidgetItemTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void DefaultConstruction();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERTREEWIDGETITEM_TEST_H
