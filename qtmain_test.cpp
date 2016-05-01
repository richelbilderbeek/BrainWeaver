#include <iostream>

#include "qtbrainweaverconceptmapdialog_test.h"
#include "qtbrainweaverclusterdialog_test.h"
#include "qtbrainweaverclusterwidget_test.h"
#include "qtbrainweavermenudialog_test.h"
#include "qtbrainweaverrateconceptmapdialog_test.h"
#include "qtbrainweavertestcreatesubconceptmapdialog_test.h"
#include "qtbrainweaverprintconceptmapdialog_test.h"
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;
  { ribi::pvdb::qtbrainweaverprintconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::pvdb::qtbrainweaverconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::pvdb::qtbrainweaverclusterdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::pvdb::qtbrainweaverclusterwidget_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::pvdb::qtbrainweavermenudialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::pvdb::qtbrainweaverrateconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::pvdb::qtbrainweavertestcreatesubconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
