#ifndef QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
#define QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace pvdb {

class qtbrainweaverconceptmapdialog_test : public QObject
{
    Q_OBJECT

private slots:
  void file_rejects_empty_concept_map();
  void file_rejects_concept_map_without_center_node();
  void file_rejects_concept_map_with_two_center_nodes();
  void file_accepts_concept_map_with_center_node();

  void a_file_its_conceptmap_must_have_a_center_node();
  void all_tests();
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTBRAINWEAVERCONCEPTMAPDIALOG_TEST_H
