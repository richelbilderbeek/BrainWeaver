#ifndef QTBRAINWEAVERRATINGDIALOG_TEST_H
#define QTBRAINWEAVERRATINGDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtRatingDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

public:
  QtRatingDialogTest();
  int m_n_hits;
public slots:
  void add_hit();

private slots:
  void default_construction();
  void default_construction_without_nodes();
  void edit_name();
  void print();
  void save();

};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERRATINGDIALOG_TEST_H
