#ifndef BRAINWEAVERCLUSTERFACTORY_H
#define BRAINWEAVERCLUSTERFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>
#include "brainweaverfwd.h"
#pragma GCC diagnostic pop

namespace ribi { namespace cmap { struct Concept; } }

namespace ribi {
namespace braw {

///Factory for creating Cluster instances
struct ClusterFactory
{
  ClusterFactory();

  Cluster Create(const std::vector<ribi::cmap::Concept>& v) const noexcept;

  int GetNumberOfTests() const noexcept { return 5; }

  ///Obtain a single test, a combination of testing node indices
  Cluster GetTest(const std::vector<int>& test_node_indices) const noexcept;

  std::vector<Cluster> GetTests() const noexcept;
};

} //~namespace braw
} //~namespace ribi

#endif // BRAINWEAVERCLUSTERFACTORY_H
