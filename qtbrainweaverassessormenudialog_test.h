#ifndef QTBRAINWEAVERASSESSORMENUDIALOG_TEST_H
#define QTBRAINWEAVERASSESSORMENUDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverassessormenudialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void click_button_about_clicked();
  void click_button_assess_result();
  void click_button_create_assessment();
  void click_button_quit();
  void default_construction();
  void press_escape();

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERASSESSORMENUDIALOG_TEST_H
