#ifndef QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
#define QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtConceptMapDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void FileHasConceptMapWithOneCenterNode();

  ///If this dialog is fed with a file with a cluster and without a concept map
  /// (that is, one node (the focal question) only)
  ///it will create a concept map from the cluster
  void FileWithOnlyClusterCreatesConceptMap();

  ///Create a concept map of two nodes and one edge with an arrow head
  ///The concept map should have saved that the arrow head is there
  //For https://github.com/richelbilderbeek/BrainWeaver/issues/88
  void CreateEdgeWithArrowHead();

  ///When a concept map is created from a Cluster with n items,
  ///it will have n+1 concepts
  void CreateFromCluster();

  ///If this dialog is fed with a file with a cluster and a concept map
  ///it will read the concept map
  void DialogPrefersReadingConceptMapOverReadingCluster();

  ///If this dialog is fed with a file without a cluster, but with concept map
  ///it will read the concept map
  void DialogPrefersExistingConceptMapOverCreatingOne();

  void PressAltF4();
  void PressEscape();
  void PressNonsense();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
