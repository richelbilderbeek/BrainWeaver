#ifndef QTBRAINWEAVERMENUDIALOG_TEST_H
#define QTBRAINWEAVERMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweavermenudialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construction();
  void press_all_keys();

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERMENUDIALOG_TEST_H
