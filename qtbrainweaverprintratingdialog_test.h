#ifndef QTBRAINWEAVERPRINTRATINGDIALOG_TEST_H
#define QTBRAINWEAVERPRINTRATINGDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtPrintRatingDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construction();
  void default_construction_without_nodes();
  void print_should_produce_file();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERPRINTRATINGDIALOG_TEST_H
