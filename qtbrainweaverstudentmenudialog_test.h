#ifndef QTBRAINWEAVERSTUDENTMENUDIALOG_TEST_H
#define QTBRAINWEAVERSTUDENTMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverstudentmenudialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void click_button_about_clicked();
  void click_button_start();
  void default_construction();
  void press_escape();
  void save();
  void set_and_get_name();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTMENUDIALOG_TEST_H
