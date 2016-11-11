#ifndef QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_TEST_H
#define QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverprintconceptmapdialog_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construct();
  void print_should_produce_file();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_TEST_H
