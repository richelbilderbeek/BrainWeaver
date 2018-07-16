#include "brainweaverfilefactory.h"
#include <boost/test/unit_test.hpp>

#include "conceptmapfactory.h"
#include "brainweaverclusterfactory.h"
#include "conceptmap.h"
#include "brainweavercluster.h"
#include "brainweaverclusterfactory.h"
#include "brainweaverfile.h"
#include "trace.h"


BOOST_AUTO_TEST_CASE(ribi_pvdb_filefactory_test)
{
  ribi::braw::FileFactory f;
  BOOST_CHECK_EQUAL(f.GetNumberOfTests(), static_cast<int>(f.GetTests().size()));
}
