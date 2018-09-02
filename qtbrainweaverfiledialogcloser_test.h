#ifndef QTBRAINWEAVERFILEDIALOGDIALOGCLOSER_TEST_H
#define QTBRAINWEAVERFILEDIALOGDIALOGCLOSER_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtFileDialogCloserTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void PressCancel() const noexcept;
  void PressOk() const noexcept;
};

} //~namespace cmap
} //~namespace braw

#endif // QTBRAINWEAVERFILEDIALOGDIALOGCLOSER_TEST_H
