#include <iostream>

#include "qtbrainweaverconceptmapdialog_test.h"
#include "qtbrainweaverclusterdialog_test.h"
#include "qtbrainweaverclusterwidget_test.h"
#include "qtbrainweavermenudialog_test.h"
#include "qtbrainweaverrateconceptmapdialog_test.h"
#include "qtbrainweaverprintconceptmapdialog_test.h"
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;
  { ribi::braw::qtbrainweavermenudialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverprintconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverclusterdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverclusterwidget_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverrateconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
