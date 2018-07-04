#ifndef QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
#define QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverconceptmapdialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void a_file_its_conceptmap_must_have_a_center_node();

  ///If this dialog is fed with a file with a cluster and without a concept map
  /// (that is, one node (the focal question) only)
  ///it will create a concept map from the cluster
  void a_file_with_cluster_only_will_create_a_concept_map();

  ///Create a concept map of two nodes and one edge with an arrow head
  ///The concept map should have saved that the arrow head is there
  //For https://github.com/richelbilderbeek/Brainweaver/issues/88
  void create_edge_with_arrow_head();

  ///When a concept map is created from a Cluster with n items,
  ///it will have n+1 concepts
  void create_from_cluster();

  ///If this dialog is fed with a file with a cluster and a concept map
  ///it will read the concept map
  void dialog_will_prefer_to_read_a_concept_map_over_a_cluster();

  ///If this dialog is fed with a file without a cluster, but with concept map
  ///it will read the concept map
  void dialog_will_prefer_to_read_an_existing_concept_map_over_creating_one();

  void press_alt_f4();
  void press_escape();
  void press_nonsense();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
