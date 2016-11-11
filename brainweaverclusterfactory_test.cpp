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
  ribi::braw::ClusterFactory f;
  BOOST_CHECK_EQUAL(f.GetNumberOfTests(), static_cast<int>(f.GetTests().size()));
}
