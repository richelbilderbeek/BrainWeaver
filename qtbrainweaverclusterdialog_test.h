#ifndef QTBRAINWEAVERCLUSTERDIALOG_TEST_H
#define QTBRAINWEAVERCLUSTERDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverclusterdialog_test : public QObject
{
    Q_OBJECT

private slots:
  void enable_button_depending_on_file();
  void cluster_dialog_must_be_enabled_if_there_is_no_concept_map();
  void cluster_dialog_must_be_disabled_if_there_are_nodes_in_the_concept_map();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERDIALOG_TEST_H
