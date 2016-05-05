#ifndef QTBRAINWEAVERMENUDIALOG_TEST_H
#define QTBRAINWEAVERMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace pvdb {

class qtbrainweavermenudialog_test : public QObject
{
    Q_OBJECT

public slots:
  void choose_file();

private slots:
  void scenario_1();
  void scenario_2();
  void press_all_buttons();

};

} //~namespace pvdb
} //~namespace ribi

#endif // QTBRAINWEAVERMENUDIALOG_TEST_H
