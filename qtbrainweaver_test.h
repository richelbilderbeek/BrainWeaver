#ifndef QTBRAINWEAVERTEST_H
#define QTBRAINWEAVERTEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

///These tests are for bigger scenario's, testing the flow of multiple dialogs
class QtTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:

  void ModifiedFileAfterClusterOkFromMenu() const noexcept;

  /// From a QtClusterDialog, pressing Next, an edit concept map dialog starts.
  /// Click OK there results in the QtClusterDialog having a modified file.
  void ModifiedFileAfterConceptMapOkFromCluster() const noexcept;

  /// From a StudentStartDialog, read edit concept map dialog starts.
  /// Click OK there results in the QtClusterDialog having a modified file.
  void ModifiedFileAfterConceptMapOkFromStart() const noexcept;

  /// From a QtClusterDialog, pressing Next, an edit concept map dialog starts.
  /// Cancelling it results in the QtClusterDialog having the same file as before.
  void SameFileAfterEditConceptMapCancelled() const noexcept;

  void Issue308() const noexcept;

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERTEST_H
