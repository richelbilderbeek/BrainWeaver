#include "qtbrainweavertestcreatesubconceptmapdialog.h"
#include <boost/test/unit_test.hpp>

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "qtconceptmap.h"
#include "ui_qtbrainweavertestcreatesubconceptmapdialog.h"

BOOST_AUTO_TEST_CASE(ribi_pvdb_QtPvdbTestCreateSubConceptMapDialog_test)
{
  using namespace ribi::pvdb;
  QtPvdbTestCreateSubConceptMapDialog d;
  const int max = d.GetUi()->box_index->maximum();
  for (int i=0; i!=max; ++i)
  {
    d.GetUi()->box_index->setValue(i);

    const int max_sub = d.GetUi()->box_index_sub->maximum();
    for (int j=0; j!=max_sub; ++j)
    {
      d.GetUi()->box_index_sub->setValue(j);
    }
  }
}
