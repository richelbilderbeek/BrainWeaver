#ifndef BRAINWEAVERCLUSTER_H
#define BRAINWEAVERCLUSTER_H

#include <map>
#include <vector>
#include "brainweaverfwd.h"
#include "conceptmapconcept.h"

namespace ribi {
namespace braw {

struct ClusterFactory;

///The data behind a QtClusterWidget
class Cluster
{
  public:
  Cluster(const std::vector<ribi::cmap::Concept>& v = {});

  ///See if the cluster is empty
  bool Empty() const noexcept;

  ///Obtain the list of Concepts
  const std::vector<ribi::cmap::Concept>& Get() const noexcept{ return m_v; }
        std::vector<ribi::cmap::Concept>& Get()       noexcept{ return m_v; }

  ///Set the concepts
  void SetConcepts(const std::vector<ribi::cmap::Concept>& concepts);

  private:
  ///A Cluster is a list of Concepts. The Concepts contain examples.
  std::vector<ribi::cmap::Concept> m_v;
};

///Convert XML to a Cluster
Cluster XmlToCluster(const std::string& s);

///Convert a Cluster from an XML std::string
std::string ToXml(const Cluster& c) noexcept;

bool operator==(const Cluster& lhs, const Cluster& rhs) noexcept;
bool operator!=(const Cluster& lhs, const Cluster& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const Cluster& c) noexcept;

} //~namespace braw
} //~namespace ribi


#endif // BRAINWEAVERCLUSTER_H
