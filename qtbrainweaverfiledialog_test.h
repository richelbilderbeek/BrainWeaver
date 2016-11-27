#ifndef QTBRAINWEAVERFILEDIALOG_TEST_H
#define QTBRAINWEAVERFILEDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverfiledialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construction();
  void save_dialog_should_say_sla_op(); //123
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERFILEDIALOG_TEST_H
