#ifndef QTBRAINWEAVERABOUTDIALOG_TEST_H
#define QTBRAINWEAVERABOUTDIALOG_TEST_H

#include <QtTest/QtTest>

namespace ribi {
namespace braw {

class QtAboutDialogTest : public QObject
{
    Q_OBJECT //!OCLINT

private slots:
  void default_construction();
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERABOUTDIALOG_TEST_H
