//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "brainweaverfilefactory.h"

#include <cassert>
#include "conceptmapfactory.h"
#include "brainweaverclusterfactory.h"
#include "conceptmap.h"
#include "brainweavercluster.h"
#include "brainweaverclusterfactory.h"
#include "brainweaverfile.h"
#include "trace.h"
#pragma GCC diagnostic pop

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
  File f;
  f.SetStudentName("ribi::braw::FileFactory::GetTests()[5] name");
  const ConceptMap concept_map = ConceptMapFactory().Get6();
  assert(boost::num_vertices(concept_map)); //Cannot set empty concept map
  f.SetQuestion(GetFirstNode(concept_map).GetName());
  f.SetConceptMap(concept_map);
  const Cluster cluster = ClusterFactory().GetTests().at(3);
  f.SetCluster(cluster);
  return f;
}

std::vector<ribi::braw::File> ribi::braw::FileFactory::GetTests() const noexcept
{
  std::vector<File > v;
  v.reserve(6);
  v.push_back(Get0());
  v.push_back(Get1());
  v.push_back(Get2());
  v.push_back(Get3());
  v.push_back(Get4());
  v.push_back(Get5());
  assert(GetNumberOfTests() == static_cast<int>(v.size()));
  return v;
}
