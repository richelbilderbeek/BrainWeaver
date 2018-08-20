#ifndef QTBRAINWEAVERCLUSTERDIALOG_TEST_H
#define QTBRAINWEAVERCLUSTERDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtClusterDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void button_add_clicked_nothing_to_add();
  void button_add_clicked_something_to_add();
  void button_next_clicked_no_concept_map();
  void button_next_clicked_with_concept_map();
  void cluster_dialog_must_be_enabled_if_there_is_no_concept_map();
  void cluster_dialog_must_be_disabled_if_there_are_nodes_in_the_concept_map();
  void default_construct();
  void enable_button_depending_on_file();
  void get_widget();
  void press_escape();
  void press_something();
  void save();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERDIALOG_TEST_H
