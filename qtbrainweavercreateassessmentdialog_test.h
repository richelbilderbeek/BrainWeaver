#ifndef QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_TEST_H
#define QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweavercreateassessmentdialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void close_on_escape();
  void default_construction();
  void has_correct_default_rating();
  void save();
  void set_and_get_question();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_TEST_H
