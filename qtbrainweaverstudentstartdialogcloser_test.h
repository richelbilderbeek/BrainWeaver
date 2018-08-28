#ifndef QTBRAINWEAVERSTUDENTSTARTDIALOGDIALOGCLOSER_TEST_H
#define QTBRAINWEAVERSTUDENTSTARTDIALOGDIALOGCLOSER_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtStudentStartDialogCloserTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void Close() const noexcept;
  void PressStartCluster() const noexcept;
  void PressStartConceptMap() const noexcept;
};

} //~namespace cmap
} //~namespace braw

#endif // QTBRAINWEAVERSTUDENTSTARTDIALOGDIALOGCLOSER_TEST_H
