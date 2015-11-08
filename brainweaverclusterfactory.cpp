//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2015 The Brainweaver Team

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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "brainweaverclusterfactory.h"

#include <cassert>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "brainweavercluster.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::pvdb::ClusterFactory::ClusterFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::pvdb::Cluster> ribi::pvdb::ClusterFactory::Create(const std::vector<ribi::cmap::Concept>& v) const noexcept
{
  const boost::shared_ptr<pvdb::Cluster> p(new pvdb::Cluster(v));
  assert(p);
  return p;
}

#ifndef NDEBUG
boost::shared_ptr<ribi::pvdb::Cluster> ribi::pvdb::ClusterFactory::DeepCopy(const boost::shared_ptr<const pvdb::Cluster> cluster) const noexcept
{
  const std::vector<ribi::cmap::Concept> v = cluster->Get();
  std::vector<ribi::cmap::Concept> w;
  std::transform(v.begin(),v.end(),std::back_inserter(w),
    [](const ribi::cmap::Concept& c)
    {
      const ribi::cmap::Concept d(c);
      assert(c == d);
      return d;
    }
  );

  boost::shared_ptr<pvdb::Cluster> p(new Cluster(w));
  assert(p);
  assert(p != cluster);
  assert(operator==(*p,*cluster));
  return p;
}
#endif

boost::shared_ptr<ribi::pvdb::Cluster> ribi::pvdb::ClusterFactory::GetTest(const std::vector<int>& test_node_indices) const noexcept
{
  std::vector<ribi::cmap::Concept> concepts;
  std::transform(test_node_indices.begin(),test_node_indices.end(),std::back_inserter(concepts),
    [](const int index)
    {
      const std::vector<ribi::cmap::Concept> tmp = cmap::ConceptFactory().GetTests();
      assert(index < static_cast<int>(cmap::ConceptFactory().GetTests().size()));
      const cmap::Concept concept = tmp.at(index);
      return concept;
    }
  );
  boost::shared_ptr<pvdb::Cluster> cluster(new Cluster(concepts));
  assert(cluster);
  return cluster;
}

std::vector<boost::shared_ptr<ribi::pvdb::Cluster> > ribi::pvdb::ClusterFactory::GetTests() const noexcept
{
  std::vector<boost::shared_ptr<pvdb::Cluster> > v(6);
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {0} );
    assert(p);
    v[0] = p;
  }
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {1} );
    assert(p);
    v[1] = p;
  }
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {0,1} );
    assert(p);
    v[2] = p;
  }
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {0,1,2} );
    assert(p);
    v[3] = p;
  }
  {
    const boost::shared_ptr<pvdb::Cluster> p = GetTest( {} );
    assert(p);
    v[4] = p;
  }
  {
    //NULLPTR
    const boost::shared_ptr<pvdb::Cluster> p;
    assert(!p);
    v[5] = p;
  }
  /* DO NOT DO THIS FOR WINE
  const std::vector<boost::shared_ptr<pvdb::Cluster> > v
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


#ifndef NDEBUG
void ribi::pvdb::ClusterFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    Cluster cluster(ribi::cmap::ConceptFactory().GetTests());
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  ClusterFactory f;
  if (f.GetNumberOfTests() != static_cast<int>(f.GetTests().size()))
  {
    TRACE(f.GetNumberOfTests());
    TRACE(f.GetTests().size());
  }
  assert(f.GetNumberOfTests() == static_cast<int>(f.GetTests().size()));
}
#endif
