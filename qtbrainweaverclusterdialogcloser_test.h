#ifndef QTBRAINWEAVERCLUSTERDIALOGDIALOGCLOSER_TEST_H
#define QTBRAINWEAVERCLUSTERDIALOGDIALOGCLOSER_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtClusterDialogCloserTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void PressCancel() const noexcept;
  void PressOk() const noexcept;
};

} //~namespace cmap
} //~namespace braw

#endif // QTBRAINWEAVERCLUSTERDIALOGDIALOGCLOSER_TEST_H
