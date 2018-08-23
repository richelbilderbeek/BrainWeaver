#ifndef QTBRAINWEAVERTEST_H
#define QTBRAINWEAVERTEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

///These tests are for bigger scenario's, testing the flow of multiple dialogs
class QtTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void Issue308() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERTEST_H
