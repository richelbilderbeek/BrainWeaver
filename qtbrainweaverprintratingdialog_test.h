#ifndef QTBRAINWEAVERPRINTRATINGDIALOG_TEST_H
#define QTBRAINWEAVERPRINTRATINGDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverprintratingdialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construction();
  void default_construction_without_nodes();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERPRINTRATINGDIALOG_TEST_H
