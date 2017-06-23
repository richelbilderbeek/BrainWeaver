#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "brainweaverclusterfactory.h"

#include <cassert>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "brainweavercluster.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#pragma GCC diagnostic pop

ribi::braw::ClusterFactory::ClusterFactory()
{

}

ribi::braw::Cluster ribi::braw::ClusterFactory::Create(
  const std::vector<ribi::cmap::Concept>& v
) const noexcept
{
  Cluster p(v);
  return p;
}

ribi::braw::Cluster ribi::braw::ClusterFactory::GetTest(
  const std::vector<int>& test_node_indices
) const noexcept
{
  std::vector<ribi::cmap::Concept> concepts;
  std::transform(
    test_node_indices.begin(),
    test_node_indices.end(),
    std::back_inserter(concepts),
    [](const int index)
    {
      const auto tmp = cmap::ConceptFactory().GetTests();
      assert(
        index < static_cast<int>(cmap::ConceptFactory().GetTests().size())
      );
      const cmap::Concept concept = tmp.at(index);
      return concept;
    }
  );
  return Cluster(concepts);
}

std::vector<ribi::braw::Cluster>
ribi::braw::ClusterFactory::GetTests() const noexcept
{
  std::vector<Cluster> v(5);
  {
    const Cluster p = GetTest( {0} );
    v[0] = p;
  }
  {
    const Cluster p = GetTest( {1} );
    v[1] = p;
  }
  {
    const Cluster p = GetTest( {0,1} );
    v[2] = p;
  }
  {
    const Cluster p = GetTest( {0,1,2} );
    v[3] = p;
  }
  {
    const Cluster p = GetTest( {} );
    v[4] = p;
  }
  /* DO NOT DO THIS FOR WINE
  const std::vector<Cluster > v
    =
    {
      GetTest( {0} ),
      GetTest( {1} ),
      GetTest( {0,1} ),
      GetTest( {0,1,2} ),
      GetTest( { } )
    };
  */
  return v;
}
