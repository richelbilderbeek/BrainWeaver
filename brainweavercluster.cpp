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
#include "brainweaverregex.h"
#include "ribi_regex.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

ribi::braw::Cluster::Cluster(const std::vector<ribi::cmap::Concept>& v)
  : m_v(v)
{

}

void ribi::braw::Cluster::Add(const ribi::cmap::Concept & concept)
{
  assert(concept.GetRatingComplexity() >= -1);
  assert(concept.GetRatingComplexity() <=  2);
  m_v.push_back(concept);

}

bool ribi::braw::Cluster::Empty() const
{
  return m_v.empty();
}

ribi::braw::Cluster ribi::braw::XmlToCluster(const std::string &s)
{
  assert(s.size() >= 19);
  assert(s.substr(0,9) == "<cluster>");
  assert(s.substr(s.size() - 10,10) == "</cluster>");
  const ribi::braw::Regex r;
  std::vector<ribi::cmap::Concept> concepts;

  //Obtain the <cluster> ... </cluster> string

  const std::vector<std::string> v = ribi::Regex().GetRegexMatches(
    s, r.GetRegexCluster()
  );
  assert(v.size() == 1);
  //Strip the <cluster> tags
  const std::string cluster_str = ribi::xml::StripXmlTag(v[0]);
  //Obtain the <concept> ... </concept> strings
  const std::vector<std::string> w = ribi::Regex().GetRegexMatches(
    cluster_str, r.GetRegexConcept()
  );
  std::for_each(w.begin(),w.end(),
    [&concepts](const std::string& s)
    {
      concepts.push_back(ribi::cmap::XmlToConcept(s));
    }
  );

  Cluster cluster(concepts);
  return cluster;
}

void ribi::braw::Cluster::SetConcepts(const std::vector<ribi::cmap::Concept>& concepts)
{
  m_v = concepts;
}

std::string ribi::braw::ToXml(const Cluster& cluster) noexcept
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

bool ribi::braw::operator==(const ribi::braw::Cluster& lhs, const ribi::braw::Cluster& rhs) noexcept
{
  const std::vector<ribi::cmap::Concept> lhs_concepts = lhs.Get();
  const std::vector<ribi::cmap::Concept> rhs_concepts = rhs.Get();
  if (lhs_concepts.size() != rhs_concepts.size())
  {
    return false;
  }
  const int sz = static_cast< int>(lhs_concepts.size());
  for (int i=0; i!=sz; ++i)
  {
    if (lhs_concepts[i] != rhs_concepts[i])
    {
      return false;
    }
  }
  return true;
}

bool ribi::braw::operator!=(const ribi::braw::Cluster& lhs, const ribi::braw::Cluster& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::braw::operator<<(std::ostream& os, const ribi::braw::Cluster& c) noexcept
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
