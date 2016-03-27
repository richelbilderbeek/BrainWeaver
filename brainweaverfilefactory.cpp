//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 The Brainweaver Team

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

ribi::pvdb::FileFactory::FileFactory()
{

}

std::vector<ribi::pvdb::File> ribi::pvdb::FileFactory::GetTests() const noexcept
{
  using ribi::cmap::ConceptMap;
  using ribi::cmap::ConceptMapFactory;
  std::vector<File > v;
  //[0]: empty file
  {
    v.push_back(File());
  }
  //[1]: file with focal question
  {
    File f;
    const ConceptMap concept_map = ConceptMapFactory().Get0();
    f.SetConceptMap(concept_map);
    v.push_back(f);
  }
  //[2]: file with complex concept map
  {
    File f;
    const ConceptMap concept_map = ConceptMapFactory().Get6();
    f.SetConceptMap(concept_map);
    v.push_back(f);
  }
  //[3]: file with complex concept map and complex cluster
  {
    File f;
    f.SetStudentName("ribi::pvdb::FileFactory::GetTests()[3] name");
    const ConceptMap concept_map = ConceptMapFactory().Get6();
    f.SetConceptMap(concept_map);
    const Cluster cluster = ClusterFactory().GetTests().at(3);
    f.SetCluster(cluster);
    v.push_back(f);
  }
  //[4]: file with rated complex concept map and complex cluster
  {
    File f;
    f.SetStudentName("ribi::pvdb::FileFactory::GetTests()[4] name");
    const ConceptMap concept_map = ConceptMapFactory().Get6();
    f.SetConceptMap(concept_map);
    const Cluster cluster = ClusterFactory().GetTests().at(3);
    f.SetCluster(cluster);
    v.push_back(f);
  }
  //[5]: file with rated complex concept map and complex cluster, all multiple lines
  {
    File f;
    f.SetStudentName("ribi::pvdb::FileFactory::GetTests()[5] name");
    const ConceptMap concept_map = ConceptMapFactory().Get6();
    f.SetConceptMap(concept_map);
    const Cluster cluster = ClusterFactory().GetTests().at(3);
    f.SetCluster(cluster);
    v.push_back(f);
  }
  return v;
}
