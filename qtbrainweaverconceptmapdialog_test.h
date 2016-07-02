#ifndef QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
#define QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverconceptmapdialog_test : public QObject
{
    Q_OBJECT

private slots:
  void a_file_its_conceptmap_must_have_a_center_node();
  void all_tests();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
