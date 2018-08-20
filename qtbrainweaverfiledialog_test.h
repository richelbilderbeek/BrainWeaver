#ifndef QTBRAINWEAVERFILEDIALOG_TEST_H
#define QTBRAINWEAVERFILEDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtFileDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construction();

  void open_dialog_should_say_kijk_in();
  void open_dialog_should_say_open();
  void open_dialog_should_say_bestanden();
  void open_dialog_should_say_soort_bestanden();
  void save_dialog_should_say_kijk_in(); //123
  void save_dialog_should_say_sla_op(); //123
  void save_dialog_should_say_bestanden(); //126
  void save_dialog_should_say_soort_bestanden(); //126
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERFILEDIALOG_TEST_H
