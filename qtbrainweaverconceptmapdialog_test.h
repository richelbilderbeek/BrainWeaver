#ifndef QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
#define QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtConceptMapDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:

  //To review
  void ExportToPdfCreatesFile() const noexcept;

  //Done

  ///Create a concept map of two nodes and one edge with an arrow head
  ///The concept map should have saved that the arrow head is there
  //For https://github.com/richelbilderbeek/BrainWeaver/issues/88
  void CreateEdgeWithArrowHead() const noexcept;

  ///When a concept map is created from a Cluster with n items,
  ///it will have n+1 concepts
  void CreateFromCluster() const noexcept;

  ///If this dialog is fed with a file with a cluster and a concept map
  ///it will read the concept map
  void DialogPrefersReadingConceptMapOverReadingCluster() const noexcept;

  ///If this dialog is fed with a file without a cluster, but with concept map
  ///it will read the concept map
  void DialogPrefersExistingConceptMapOverCreatingOne() const noexcept;


  void FileHasConceptMapWithOneCenterNode() const noexcept;

  ///If this dialog is fed with a file with a cluster and without a concept map
  /// (that is, one node (the focal question) only)
  ///it will create a concept map from the cluster
  void FileWithOnlyClusterCreatesConceptMap() const noexcept;

  void PressAltF4() const noexcept;
  void PressEscapeClosesDialog() const noexcept;
  void PressNonsense() const noexcept;

  void QuickSaveFirstTimeOpensDialog() const noexcept;
  void QuickSaveSecondTimeSavesFast() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
