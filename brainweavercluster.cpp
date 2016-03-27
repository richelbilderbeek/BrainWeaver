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
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "brainweavercluster.h"

#include <sstream>
#include <QRegExp>

#include "conceptmapcompetency.h"
#include "brainweaverhelper.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapconcept.h"
#include "conceptmapconceptfactory.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::pvdb::Cluster::Cluster(const std::vector<ribi::cmap::Concept>& v)
  : m_v(v)
{

}

void ribi::pvdb::Cluster::Add(const ribi::cmap::Concept & concept)
{
  assert(concept.GetRatingComplexity() >= -1);
  assert(concept.GetRatingComplexity() <=  2);
  m_v.push_back(concept);

}

bool ribi::pvdb::Cluster::Empty() const
{
  return m_v.empty();
}

ribi::pvdb::Cluster ribi::pvdb::XmlToCluster(const std::string &s)
{
  assert(s.size() >= 19);
  assert(s.substr(0,9) == "<cluster>");
  assert(s.substr(s.size() - 10,10) == "</cluster>");

  std::vector<ribi::cmap::Concept> concepts;

  //Obtain the <cluster> ... </cluster> string
  const std::vector<std::string> v
    = ribi::pvdb::GetRegexMatches(s,QRegExp("(<cluster>.*</cluster>)"));
  assert(v.size() == 1);
  //Strip the <cluster> tags
  const std::string cluster_str = ribi::xml::StripXmlTag(v[0]);
  //Obtain the <concept> ... </concept> strings
  const std::vector<std::string> w
    = pvdb::GetRegexMatches(s,QRegExp("(<concept>.*</concept>)"));
  std::for_each(w.begin(),w.end(),
    [&concepts](const std::string& s)
    {
      concepts.push_back(ribi::cmap::XmlToConcept(s));
    }
  );

  pvdb::Cluster cluster(concepts);
  return cluster;
}

void ribi::pvdb::Cluster::SetConcepts(const std::vector<ribi::cmap::Concept>& concepts)
{
  m_v = concepts;
}

std::string ribi::pvdb::ToXml(const pvdb::Cluster& cluster) noexcept
{
  std::stringstream s;
  s << "<cluster>";
  {
    const std::vector<ribi::cmap::Concept>& v = cluster.Get();
    std::for_each(v.begin(), v.end(),
      [&s](const ribi::cmap::Concept& concept)
      {
        s << ribi::cmap::ToXml(concept);
      }
    );
  }
  s << "</cluster>";

  const std::string r = s.str();
  assert(r.size() >= 19);
  assert(r.substr(0,9) == "<cluster>");
  assert(r.substr(r.size() - 10,10) == "</cluster>");

  return r;
}

bool ribi::pvdb::operator==(const ribi::pvdb::Cluster& lhs, const ribi::pvdb::Cluster& rhs) noexcept
{
  const bool verbose{false};
  const std::vector<ribi::cmap::Concept> lhs_concepts = lhs.Get();
  const std::vector<ribi::cmap::Concept> rhs_concepts = rhs.Get();
  if (lhs_concepts.size() != rhs_concepts.size())
  {
    if (verbose) { TRACE("Number of concepts differ"); }
    return false;
  }
  const int sz = static_cast< int>(lhs_concepts.size());
  for (int i=0; i!=sz; ++i)
  {
    if (lhs_concepts[i] != rhs_concepts[i])
    {
      if (verbose) { TRACE("A concepts differs"); }
      return false;
    }
  }
  return true;
}

bool ribi::pvdb::operator!=(const ribi::pvdb::Cluster& lhs, const ribi::pvdb::Cluster& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::pvdb::operator<<(std::ostream& os, const ribi::pvdb::Cluster& c) noexcept
{
  const auto v = c.Get();
  std::stringstream s;
  std::copy(std::begin(v), std::end(v), std::ostream_iterator<ribi::cmap::Concept>(s,", "));
  std::string t;
  s << t;
  if (!t.empty())
  {
    t.pop_back();
    assert(!t.empty());
    t.pop_back();
  }
  os << t;
  return os;
}
