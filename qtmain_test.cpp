#include <cassert>
#include <iostream>

#include "qtbrainweaveraboutdialog_test.h"
#include "qtbrainweaverassessormenudialog_test.h"
#include "qtbrainweaverclusterdialog_test.h"
#include "qtbrainweaverclustertreewidgetitem_test.h"
#include "qtbrainweaverclusterwidget_test.h"
#include "qtbrainweaverconceptmapdialog_test.h"
#include "qtbrainweavercreateassessmentdialog_test.h"
#include "qtbrainweaverdisplay_test.h"
#include "qtbrainweaverfiledialog_test.h"
#include "qtbrainweavermenudialog_test.h"
#include "qtbrainweaveroverviewdialog_test.h"
#include "qtbrainweaveroverviewwidget_test.h"
#include "qtbrainweaverprintconceptmapdialog_test.h"
#include "qtbrainweaverprintratingdialog_test.h"
#include "qtbrainweaverrateconceptmapdialog_test.h"
#include "qtbrainweaverratingdialog_test.h"
#include "qtbrainweaverstudentmenudialog_test.h"
#include "qtbrainweaverstudentstartcompletedialog_test.h"

#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;
  //{ ribi::braw::qtbrainweavercreateassessmentdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  //{ ribi::braw::qtbrainweaverratingdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  //{ ribi::braw::qtbrainweaverfiledialog_test t; error |= QTest::qExec(&t, argc, argv); }
  //{ ribi::braw::qtbrainweaverrateconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  //{ ribi::braw::qtbrainweaverprintratingdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  //{ ribi::braw::qtbrainweaverconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  //{ ribi::braw::qtbrainweaveroverviewdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  //{ ribi::braw::qtbrainweaveroverviewwidget_test t; error |= QTest::qExec(&t, argc, argv); }
  //{ ribi::braw::QtBrainWeaverMenuDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  //assert(!"Do not forget to comment this out on Travis");

  { ribi::braw::qtbrainweaveraboutdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverassessormenudialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverclusterdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverclustertreewidgetitem_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverclusterwidget_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweavercreateassessmentdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverdisplay_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverfiledialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtBrainWeaverMenuDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaveroverviewdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaveroverviewwidget_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverprintconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverprintratingdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverrateconceptmapdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverratingdialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverstudentmenudialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::qtbrainweaverstudentstartcompletedialog_test t; error |= QTest::qExec(&t, argc, argv); }

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
