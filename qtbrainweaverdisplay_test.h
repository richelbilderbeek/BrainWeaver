#ifndef QTBRAINWEAVERDISPLAY_TEST_H
#define QTBRAINWEAVERDISPLAY_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverdisplay_test : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construction();
  void display_examples();
  void display_misc_values();
  void display_misc_values_without_center_node();
  void display_rated_concepts();
  void display_rated_concepts_without_center_node();
  void display_values();
  void display_values_without_nodes();
};

} //~namespace braw
} //~namespace ribi



#endif // QTBRAINWEAVERDISPLAY_TEST_H
