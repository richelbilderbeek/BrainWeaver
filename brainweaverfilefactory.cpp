

#include "brainweaverfilefactory.h"

#include <cassert>
#include "conceptmapfactory.h"
#include "brainweaverclusterfactory.h"
#include "conceptmap.h"
#include "brainweavercluster.h"
#include "brainweaverclusterfactory.h"
#include "brainweaverfile.h"


ribi::braw::FileFactory::FileFactory()
{

}

ribi::braw::File ribi::braw::FileFactory::Get0() const noexcept
{
  File f;
  f.SetQuestion("File::Test[0]");
  return f;
}

ribi::braw::File ribi::braw::FileFactory::Get1() const noexcept
{
  using ribi::cmap::ConceptMap;
  using ribi::cmap::ConceptMapFactory;
  File f;
  const ConceptMap concept_map = ConceptMapFactory().Get1();
  assert(boost::num_vertices(concept_map)); //Cannot set empty concept map
  f.SetQuestion(GetFirstNode(concept_map).GetName());
  f.SetConceptMap(concept_map);
  return f;
}

ribi::braw::File ribi::braw::FileFactory::Get2() const noexcept
{
  using ribi::cmap::ConceptMap;
  using ribi::cmap::ConceptMapFactory;
  File f;
  const ConceptMap concept_map = ConceptMapFactory().Get6();
  assert(boost::num_vertices(concept_map)); //Cannot set empty concept map
  f.SetQuestion(GetFirstNode(concept_map).GetName());
  f.SetConceptMap(concept_map);
  return f;
}

ribi::braw::File ribi::braw::FileFactory::Get3() const noexcept
{
  using ribi::cmap::ConceptMap;
  using ribi::cmap::ConceptMapFactory;
  File f;
  f.SetStudentName("ribi::braw::FileFactory::GetTests()[3] name");
  const ConceptMap concept_map = ConceptMapFactory().Get6();
  assert(boost::num_vertices(concept_map)); //Cannot set empty concept map
  f.SetQuestion(GetFirstNode(concept_map).GetName());
  f.SetConceptMap(concept_map);
  const Cluster cluster = ClusterFactory().GetTests().at(3);
  f.SetCluster(cluster);
  return f;
}

ribi::braw::File ribi::braw::FileFactory::Get4() const noexcept
{
  using ribi::cmap::ConceptMap;
  using ribi::cmap::ConceptMapFactory;
  File f;
  f.SetStudentName("ribi::braw::FileFactory::GetTests()[4] name");
  const ConceptMap concept_map = ConceptMapFactory().Get6();
  assert(boost::num_vertices(concept_map)); //Cannot set empty concept map
  f.SetQuestion(GetFirstNode(concept_map).GetName());
  f.SetConceptMap(concept_map);
  const Cluster cluster = ClusterFactory().GetTests().at(3);
  f.SetCluster(cluster);
  return f;
}

ribi::braw::File ribi::braw::FileFactory::Get5() const noexcept
{
  using ribi::cmap::ConceptMap;
  using ribi::cmap::ConceptMapFactory;
  using ribi::cmap::GetCenterNode;
  File f;
  f.SetStudentName("ribi::braw::FileFactory::GetTests()[5] name");
  const ConceptMap concept_map = ConceptMapFactory().Get6();
  assert(boost::num_vertices(concept_map)); //Cannot set empty concept map
  f.SetQuestion(GetCenterNode(concept_map).GetName());
  f.SetConceptMap(concept_map);
  const Cluster cluster = ClusterFactory().GetTests().at(3);
  f.SetCluster(cluster);
  assert(IsCenterNode(ribi::cmap::GetFirstNode(f.GetConceptMap())));
  return f;
}

ribi::braw::File ribi::braw::FileFactory::GetWithExamplesWithCompetencies(
  const std::vector<ribi::cmap::Competency>& competencies
) const noexcept
{
  using ribi::cmap::ConceptMap;
  using ribi::cmap::ConceptMapFactory;
  using ribi::cmap::GetCenterNode;
  File f;
  f.SetStudentName("ribi::braw::FileFactory::Get6() name");
  const ConceptMap concept_map{
    ConceptMapFactory().GetWithExamplesWithCompetencies(competencies)
  };
  assert(boost::num_vertices(concept_map)); //Cannot set empty concept map
  f.SetQuestion(GetCenterNode(concept_map).GetName());
  f.SetConceptMap(concept_map);
  return f;
}


std::vector<ribi::braw::File> ribi::braw::FileFactory::GetTests() const noexcept
{
  using ribi::cmap::Competency;
  std::vector<File > v;
  v.reserve(7);
  v.push_back(Get0());
  v.push_back(Get1());
  v.push_back(Get2());
  v.push_back(Get3());
  v.push_back(Get4());
  v.push_back(Get5());
  v.push_back(
    GetWithExamplesWithCompetencies(
      { Competency::organisations, Competency::profession }
    )
  );
  assert(GetNumberOfTests() == static_cast<int>(v.size()));
  return v;
}
