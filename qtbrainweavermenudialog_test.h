#ifndef QTBRAINWEAVERMENUDIALOG_TEST_H
#define QTBRAINWEAVERMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace pvdb {

class qtbrainweavermenudialog_test : public QObject
{
    Q_OBJECT

private slots:
  void press_all_buttons();

};

} //~namespace pvdb
} //~namespace ribi

#endif // QTBRAINWEAVERMENUDIALOG_TEST_H
