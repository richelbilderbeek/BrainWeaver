#ifndef QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_TEST_H
#define QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverstudentstartcompletedialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construction();
  void go_back_to_menu_is_false_at_construction();
  void press_escape();
  void save();
  void start_associate();
  void start_construct();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_TEST_H
