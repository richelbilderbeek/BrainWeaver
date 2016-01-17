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
#ifndef BRAINWEAVERCLUSTER_H
#define BRAINWEAVERCLUSTER_H

#include <map>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "brainweaverfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace pvdb {

struct ClusterFactory;

///The data behind a QtPvdbClusterWidget
class Cluster
{
  public:
  Cluster(const std::vector<ribi::cmap::Concept>& v = {});

  ///Add a Concept to the Cluster
  void Add(const ribi::cmap::Concept& concept);

  ///See if the cluster is empty
  bool Empty() const;

  ///Obtain a Cluster from an XML std::string
  static pvdb::Cluster FromXml(const std::string& s);

  ///Obtain the list of Concepts
  const std::vector<ribi::cmap::Concept>& Get() const noexcept{ return m_v; }
        std::vector<ribi::cmap::Concept>& Get()       noexcept{ return m_v; }

  ///Set the concepts
  void SetConcepts(const std::vector<ribi::cmap::Concept>& concepts);

  ///Convert a Cluster from an XML std::string
  static std::string ToXml(const Cluster& c) noexcept;

  private:
  ///A Cluster is a list of Concepts. The Concepts contain examples.
  std::vector<ribi::cmap::Concept> m_v;

  ///Test this class
  static void Test() noexcept;
};

bool operator==(const pvdb::Cluster& lhs, const pvdb::Cluster& rhs) noexcept;
bool operator!=(const pvdb::Cluster& lhs, const pvdb::Cluster& rhs) noexcept;

} //~namespace pvdb
} //~namespace ribi


#endif // BRAINWEAVERCLUSTER_H
