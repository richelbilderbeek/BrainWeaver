#ifndef QTBRAINWEAVERSTUDENTMENUDIALOGDIALOGCLOSER_TEST_H
#define QTBRAINWEAVERSTUDENTMENUDIALOGDIALOGCLOSER_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtStudentMenuDialogCloserTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void Close() const noexcept;
  void PressStart() const noexcept;
};

} //~namespace cmap
} //~namespace braw

#endif // QTBRAINWEAVERSTUDENTMENUDIALOGDIALOGCLOSER_TEST_H
