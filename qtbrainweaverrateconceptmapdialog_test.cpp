#include "qtbrainweaverrateconceptmapdialog_test.h"

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>

#include "qtbrainweaverrateconceptmapdialog.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "brainweaverfilefactory.h"
#include "qtbrainweaverfiledialog.h"
#include "qtscopeddisable.h"
#include "brainweaverfile.h"
#include "qtconceptmap.h"
#include "testtimer.h"
#include "trace.h"
#include "qtbrainweaverratingdialog.h"
#include "fileio.h"
#include "qtconceptmaprateconceptdialog.h"
#include "ui_qtbrainweaverrateconceptmapdialog.h"


void ribi::braw::qtbrainweaverrateconceptmapdialog_test
  ::file_must_match_getfile()
{
  for (const auto& file: FileFactory().GetTests())
  {
    if (!boost::num_vertices(file.GetConceptMap()))
    {
      //Cannot rate a null concept map
      continue;
    }
    QtRateConceptMapDialog d(file);
    d.show();
    QVERIFY(d.GetFile() == file);
  }
}

void ribi::braw::qtbrainweaverrateconceptmapdialog_test::save()
{
  const std::string filename{
    "qtbrainweaverrateconceptmapdialog_test_save.cmp"
  };
  if (ribi::is_regular_file(filename)) { ribi::delete_file(filename); }
  assert(!ribi::is_regular_file(filename));

  const File file = FileFactory().Get5();
  QtRateConceptMapDialog d(file);
  d.show();
  d.Save(filename);
  QVERIFY(ribi::is_regular_file(filename));
}

void ribi::braw::qtbrainweaverrateconceptmapdialog_test::widget_must_be_initialized()
{
  for (const auto& file: FileFactory().GetTests())
  {
    if (!boost::num_vertices(file.GetConceptMap()))
    {
      //Cannot rate a null concept map
      continue;
    }
    QtRateConceptMapDialog d(file);
    d.show();
    QVERIFY(d.GetWidget());
  }
}
