#include "qtbrainweavertestcreatesubconceptmapdialog_test.h"

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>
#include "qtbrainweavertestcreatesubconceptmapdialog.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "qtconceptmap.h"
#include "ui_qtbrainweavertestcreatesubconceptmapdialog.h"

void ribi::pvdb::qtbrainweavertestcreatesubconceptmapdialog_test::all_tests()
{
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
