#ifndef QTBRAINWEAVERCLUSTERWIDGET_TEST_H
#define QTBRAINWEAVERCLUSTERWIDGET_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtClusterWidgetTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void AddTopLevelItemWithNullptr() const noexcept;
  void HasNoItemsAtLevelThree() const noexcept;
  void ItemAbuse() const noexcept;
  void MoveJthChildToTop() const noexcept;
  void Use() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERWIDGET_TEST_H
