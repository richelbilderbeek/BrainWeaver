#ifndef QTBRAINWEAVERRATINGDIALOG_TEST_H
#define QTBRAINWEAVERRATINGDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class qtbrainweaverratingdialog_test : public QObject
{
    Q_OBJECT

private slots:
  void default_construction();
  void default_construction_without_nodes();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERRATINGDIALOG_TEST_H
