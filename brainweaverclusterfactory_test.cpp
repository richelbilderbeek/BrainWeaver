#include "brainweaverclusterfactory.h"

#include <boost/test/unit_test.hpp>

#include <vector>
#include <boost/shared_ptr.hpp>
#include "brainweavercluster.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "testtimer.h"
#include "trace.h"

BOOST_AUTO_TEST_CASE(ribi_pvdb_cluster_factory_test)
{
  using namespace ribi::pvdb;
  ClusterFactory f;
  if (f.GetNumberOfTests() != static_cast<int>(f.GetTests().size()))
  {
    TRACE(f.GetNumberOfTests());
    TRACE(f.GetTests().size());
  }
  BOOST_CHECK(f.GetNumberOfTests() == static_cast<int>(f.GetTests().size()));
}
