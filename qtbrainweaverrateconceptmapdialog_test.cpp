#include "qtbrainweaverrateconceptmapdialog.h"
#include <boost/test/unit_test.hpp>


#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>

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

#include "qtconceptmaprateconceptdialognewname.h"
#include "ui_qtbrainweaverrateconceptmapdialog.h"

BOOST_AUTO_TEST_CASE(ribi_pvdb_qtrateconceptmapdialog_test)
{
  using namespace ribi::pvdb;
  const int test_depth = 1;

  if (test_depth > 1)
  {
    const auto v = FileFactory().GetTests();
    const int sz = boost::numeric_cast<int>(v.size());
    for (int i=0; i!=sz; ++i)
    {
      const auto file = v[i];
      
      if (!boost::num_vertices(file.GetConceptMap()))
      {
        //Cannot rate a null concept map
        continue;
      }
      QtRateConceptMapDialog d(file);
      BOOST_CHECK(d.GetWidget());
    }
  }

}
