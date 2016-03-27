#include "brainweaverfilefactory.h"
#include <boost/test/unit_test.hpp>

#include "conceptmapfactory.h"
#include "brainweaverclusterfactory.h"
#include "conceptmap.h"
#include "brainweavercluster.h"
#include "brainweaverclusterfactory.h"
#include "brainweaverfile.h"
#include "trace.h"
#pragma GCC diagnostic pop

BOOST_AUTO_TEST_CASE(ribi_pvdb_filefactory_test)
{
  using namespace ribi::pvdb;
  FileFactory f;
  if (f.GetNumberOfTests() != static_cast<int>(f.GetTests().size()))
  {
    std::cerr << "Change FileFactory::GetNumberOfTests to return " << f.GetTests().size() << std::endl;
    TRACE(f.GetNumberOfTests());
    TRACE(f.GetTests().size());
  }
  BOOST_CHECK(f.GetNumberOfTests() == static_cast<int>(f.GetTests().size()));
}
