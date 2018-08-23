#ifndef QTBRAINWEAVERCONCEPTMAPDIALOGDIALOGCLOSER_TEST_H
#define QTBRAINWEAVERCONCEPTMAPDIALOGDIALOGCLOSER_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtConceptMapDialogCloserTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void Close() const noexcept;
};

} //~namespace cmap
} //~namespace braw

#endif // QTBRAINWEAVERCONCEPTMAPDIALOGDIALOGCLOSER_TEST_H
