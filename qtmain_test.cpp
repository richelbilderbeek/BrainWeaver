#include <cassert>
#include <iostream>

#include "qtbrainweaver_test.h"
#include "qtbrainweaveraboutdialog_test.h"
#include "qtbrainweaverassessormenudialog_test.h"
#include "qtbrainweaverclusterdialog_test.h"
#include "qtbrainweaverclusterdialogcloser_test.h"
#include "qtbrainweaverclustertreewidgetitem_test.h"
#include "qtbrainweaverclusterwidget_test.h"
#include "qtbrainweaverconceptmapdialog_test.h"
#include "qtbrainweaverconceptmapdialogcloser_test.h"
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
#include "qtbrainweaverstudentstartdialog_test.h"
#include "qtbrainweaverstudentstartdialogcloser_test.h"

#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;

  //{ ribi::braw::QtTest t; error |= QTest::qExec(&t, argc, argv); } //Big tests
  //assert(!"Do not forget to comment this out on Travis");

  { ribi::braw::QtAboutDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtAssessorMenuDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtClusterDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtClusterDialogCloserTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtClusterTreeWidgetItemTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtClusterWidgetTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtConceptMapDialogCloserTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtConceptMapDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtCreateAssessmentDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtDisplayTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtFileDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtMenuDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtOverviewDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtOverviewWidgetTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtPrintConceptMapDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtPrintRatingDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtRateConceptMapDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtRatingDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtStudentMenuDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtStudentStartDialogTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtStudentStartDialogCloserTest t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::braw::QtTest t; error |= QTest::qExec(&t, argc, argv); } //Big tests

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
