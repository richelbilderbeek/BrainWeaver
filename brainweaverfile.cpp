
#include "brainweaverfile.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <QDebug>
#include <QFile>
#include <QRegExp>

#include "conceptmaprating.h"
#include "conceptmapregex.h"
#include "conceptmapcenternodefactory.h"
#include "count_undirected_graph_levels.h"
#include "add_bundled_vertex.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "file_to_vector.h"
#include "graphviz_decode.h"
#include "conceptmapnode.h"
#include "conceptmaphelper.h"
#include "brainweaverregex.h"
#include "fileio.h"
#include "brainweaverclusterfactory.h"
#include "brainweavercluster.h"
#include "conceptmapregex.h"
#include "brainweaverfilefactory.h"
#include "brainweaverhelper.h"
#include "ribi_regex.h"
#include "xml.h"


ribi::braw::File::File()
  : m_about("BrainWeaver"),
    m_assessor_name{},
    m_cluster{},
    m_concept_map{},
    m_question{},
    m_rating{ribi::cmap::CreateDefaultRating()},
    m_student_name{},
    m_version("0.4")
{

}

ribi::braw::File::File(
  const std::string& about,
  const std::string& assessor_name,
  const Cluster& cluster,
  const ribi::cmap::ConceptMap& concept_map,
  const std::string& question,
  const ribi::cmap::Rating& rating,
  const std::string& student_name,
  const std::string& version)
  : m_about(about),
    m_assessor_name(assessor_name),
    m_cluster(cluster),
    m_concept_map(concept_map),
    m_question(question),
    m_rating{rating},
    m_student_name(student_name),
    m_version(version)
{

}

void ribi::braw::File::AutoSave() const
{
  //Reversed order: first a save is attempted at 'autosave2'
  //If that fails, 'autosave1' is still in a valid state
  this->Save("autosave2." + GetFilenameExtension());
  this->Save("autosave1." + GetFilenameExtension());
}

int ribi::braw::CountEdges(const File& file) noexcept
{
  return boost::num_edges(file.GetConceptMap());
}

double ribi::braw::CountEdgesPerNormalNode(
  const File& file,
  const int n_digits_behind_comma
)
{
  assert(n_digits_behind_comma >= 0);
  const auto g = file.GetConceptMap();
  std::vector<int> degrees;
  const auto vip = vertices(g);
  for (auto i = vip.first; i != vip.second; ++i)
  {
    if (IsCenterNode(g[*i])) continue;
    degrees.push_back(boost::degree(*i, g));
  }
  const int sum{std::accumulate(std::begin(degrees), std::end(degrees), 0)};
  const double adpc{ //average_degree_per_concept
    static_cast<double>(sum) / static_cast<double>(degrees.size())
  };

  //Get the right number of digits behind the comma
  const double exponent{std::pow(10, n_digits_behind_comma)};
  return std::round(adpc * exponent) / exponent;
}

int ribi::braw::CountExamples(const File& file) noexcept
{
  return CountExamples(file.GetConceptMap());
}

int ribi::braw::CountHierarchicalLevels(const File& file) noexcept
{
  const auto g = file.GetConceptMap();
  const auto vd = ribi::cmap::FindCenterNode(g);
  return count_undirected_graph_levels(vd, g);
}

int ribi::braw::CountNodes(const File& file) noexcept
{
  return boost::num_vertices(file.GetConceptMap());
}

int ribi::braw::CountPrimaryConcepts(const File& file) noexcept
{
  const auto& g = file.GetConceptMap();
  const auto vip = boost::vertices(g);
  int cnt{0};
  for (auto vi = vip.first; vi != vip.second; ++vi)
  {
    const ribi::cmap::VertexDescriptor vd = *vi;
    if (IsPrimaryConcept(vd, g)) ++cnt;
  }
  return cnt;
}

int ribi::braw::CountSecondaryConcepts(const File& file) noexcept
{
  const auto& g = file.GetConceptMap();
  const auto vip = boost::vertices(g);
  int cnt{0};
  for (auto vi = vip.first; vi != vip.second; ++vi)
  {
    const ribi::cmap::VertexDescriptor vd = *vi;
    if (IsSecondaryConcept(vd, g)) ++cnt;
  }
  return cnt;
}

std::string ribi::braw::ExtractFileAboutFromXml(const std::string& s)
{
  const std::vector<std::string> v
    = ribi::Regex().GetRegexMatches(s,ribi::braw::Regex().GetRegexAbout());
  if (v.size() != 1)
  {
    throw std::invalid_argument("Must have one about tag");
  }
  return ribi::xml::StripXmlTag(v[0]);
}

std::string ribi::braw::ExtractFileAssessorNameFromXml(const std::string& s)
{
  const std::vector<std::string> v
    = ribi::Regex().GetRegexMatches(s,ribi::braw::Regex().GetRegexAssessorName());
  if (v.size() != 1)
  {
    throw std::invalid_argument("Must have one assessor_name tag");
  }
  return ribi::xml::StripXmlTag(v[0]);
}

ribi::braw::Cluster ribi::braw::ExtractFileClusterFromXml(const std::string& s) noexcept
{
  const std::vector<std::string> v
    = ribi::Regex().GetRegexMatches(s,ribi::braw::Regex().GetRegexCluster());
  if (v.empty())
  {
    return ribi::braw::Cluster();
  }
  assert(v.size() == 1);
  return XmlToCluster(v[0]);
}


ribi::cmap::ConceptMap ribi::braw::ExtractFileConceptMapFromXml(const std::string& s) noexcept
{
  const std::vector<std::string> v
    = ribi::Regex().GetRegexMatches(
      s, ribi::braw::Regex().GetRegexConceptMap()
    );

  if (v.empty())
  {
    return ribi::cmap::ConceptMap();
  }
  assert(v.size() == 1);
  return ribi::cmap::XmlToConceptMap(v[0]);
}

std::string ribi::braw::ExtractFileQuestionFromXml(const std::string& s) noexcept
{
  const std::vector<std::string> v
    = ribi::Regex().GetRegexMatches(
      s,
      ribi::braw::Regex().GetRegexQuestion()
    );
  if (v.size() != 1)
  {
    return ""; //No question yet
  }
  return graphviz_decode(ribi::xml::StripXmlTag(v[0]));
}

ribi::cmap::Rating ribi::braw::ExtractFileRatingFromXml(const std::string& s) noexcept
{
  return ribi::cmap::XmlToRating(s);
}

std::string ribi::braw::ExtractFileStudentNameFromXml(const std::string& s)
{
  const std::vector<std::string> v = ribi::Regex().GetRegexMatches(
    s,
    ribi::braw::Regex().GetRegexStudentName()
  );
  if (v.size() != 1)
  {
    throw std::invalid_argument("Must have one student_name tag");
  }
  return ribi::xml::StripXmlTag(v[0]);
}

std::string ribi::braw::ExtractFileVersionFromXml(const std::string& s)
{
  const std::vector<std::string> v = ribi::Regex().GetRegexMatches(
    s,
    ribi::braw::Regex().GetRegexVersion()
  );
  if (v.size() != 1)
  {
    throw std::invalid_argument("Must have one version tag");
  }
  return ribi::xml::StripXmlTag(v[0]);
}

std::string ribi::braw::GetFilenameExtension() noexcept
{
  return "cmp";
}

std::string ribi::braw::File::GetQuestion() const
{
  return m_question;
}

std::string ribi::braw::GetTempFileName() noexcept
{
  return "tmp." + GetFilenameExtension();
}

std::string ribi::braw::GetTestFileName() noexcept
{
  return "test." + GetFilenameExtension();
}


std::vector<ribi::braw::File> ribi::braw::File::GetTests() noexcept
{
  std::vector<File> v;
  for (const auto cluster: ClusterFactory().GetTests())
  {
    for (const auto concept_map: cmap::ConceptMapFactory().GetAllTests())
    {
      const std::string about = "about";
      const std::string assessor_name = "assessor_name";
      std::string question = "question";
      const std::string student_name = "student_name";
      const std::string version = "version";
      File file(
        about,
        assessor_name,
        cluster,
        concept_map,
        question,
        ribi::cmap::CreateDefaultRating(),
        student_name,
        version
      );
      v.push_back(file);
    }
  }
  return v;
}

bool ribi::braw::HasSimilarData(
  const File& lhs,
  const File& rhs,
  const double tolerance
) noexcept
{
  return
     lhs.GetAssessorName() == rhs.GetAssessorName()
  && lhs.GetCluster() == rhs.GetCluster()
  && ::ribi::cmap::HasSimilarData(
    lhs.GetConceptMap(), rhs.GetConceptMap(), tolerance)
  && lhs.GetStudentName() == rhs.GetStudentName()
  && lhs.GetVersion() == rhs.GetVersion();

}

ribi::braw::File ribi::braw::LoadFile(const std::string &filename)
{
  if(!ribi::is_regular_file(filename))
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "can only convert existing files, "
      << "filename supplied: '"
      << filename << "' was not found"
    ;
    throw std::invalid_argument(msg.str());
  }

  std::string xml;
  //Read XML from file
  {
    const std::vector<std::string> v = ribi::cmap::SafeFileToVector(filename);
    //FileToVector allowed an empty line after text, due to difference in line ending
    //SafeFileToVector should remove this line

    for (const auto& s: v) { xml+=s; }

    xml.erase(std::remove(xml.begin(),xml.end(),'\r'),xml.end());
    xml.erase(std::remove(xml.begin(),xml.end(),'\t'),xml.end());
    xml.erase(std::remove(xml.begin(),xml.end(),'\n'),xml.end());
    xml.erase(std::remove(xml.begin(),xml.end(),'\b'),xml.end());

    assert(std::count(xml.begin(),xml.end(),'\n')==0);
    assert(std::count(xml.begin(),xml.end(),'\t')==0);
    assert(std::count(xml.begin(),xml.end(),'\r')==0);
    assert(std::count(xml.begin(),xml.end(),'\b')==0);
  }
  boost::algorithm::trim(xml);

  File file = ribi::braw::XmlToFile(xml);
  return file;
}

void ribi::braw::File::Save(const std::string &filename) const
{
  try
  {
    const std::string s = ToXml(*this);
    std::ofstream f(filename.c_str());
    f << s;
  }
  catch (const std::exception& e)
  {
    #ifndef NDEBUG
    qCritical() << __func__ << ": failed with exception " << e.what();
    #endif // NDEBUG
  }
}

void ribi::braw::File::SetAssessorName(const std::string& assessor_name)
{
  assert(assessor_name.size() > 1);
  m_assessor_name = assessor_name;
  this->AutoSave();
}

void ribi::braw::File::SetConceptMap(const ribi::cmap::ConceptMap& concept_map)
{
  if (boost::num_vertices(concept_map) == 0)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "cannot set an empty concept map"
    ;
    throw std::invalid_argument(msg.str());
  }
  if (CountCenterNodes(concept_map) != 1)
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "in BrainWeaver, every concept map must have exactly one center node, "
      << "supplied number of center nodes was " << CountCenterNodes(concept_map)
    ;
    throw std::invalid_argument(msg.str());
  }
  if (GetQuestion() != GetCenterNode(concept_map).GetName())
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "in BrainWeaver, the question will be put on the center node of the concept map. "
      << "However, these do not match. "
      << "Question: '" << GetQuestion() << "', "
      << "text on center node: '" << GetCenterNode(concept_map).GetName()
      << "' "
    ;
    throw std::invalid_argument(msg.str());
  }
  m_concept_map = concept_map;
  this->AutoSave();
}

void ribi::braw::File::SetCluster(const Cluster& cluster) noexcept
{
  m_cluster = cluster;
  this->AutoSave();
}

void ribi::braw::File::SetQuestion(const std::string& question)
{
  //assert(question.size() > 0);
  m_question = question;
  this->AutoSave();
}

void ribi::braw::File::SetRating(const ribi::cmap::Rating& rating)
{
  m_rating = rating;
  AutoSave();
}

void ribi::braw::File::SetStudentName(const std::string& student_name)
{
  if (student_name.empty())
  {
    throw std::invalid_argument(
      "Student must have a name with of least one character"
    );
  }
  m_student_name = student_name;
  this->AutoSave();
}

std::map<ribi::cmap::Competency,int> ribi::braw::TallyCompetencies(const File& file)
{
  //The first node removed, as this is the focal question
  assert(IsCenterNode(ribi::cmap::GetFirstNode(file.GetConceptMap())));
  const auto g = ribi::cmap::RemoveFirstNode(file.GetConceptMap());
  return ribi::cmap::TallyCompetencies(g);
}

ribi::cmap::ConceptMap ribi::braw::CreateConceptMap(
  const std::string& text) noexcept
{
  ribi::cmap::ConceptMap g;
  ribi::cmap::Node n(ribi::cmap::Concept(text), ribi::cmap::NodeType::center);
  assert(n.GetType() == ribi::cmap::NodeType::center);
  add_bundled_vertex(n, g);
  assert(ribi::cmap::CountCenterNodes(g) == 1);
  return g;
}

std::string ribi::braw::ToXml(const File& file) noexcept
{
  std::stringstream s;
  s << "<file>"
    << "<about>" << file.GetAbout() << "</about>"
    << "<assessor_name>" << file.GetAssessorName() << "</assessor_name>"
    << ToXml(file.GetCluster())
    << ribi::cmap::ToXml(file.GetConceptMap())
    << "<question>" << file.GetQuestion() << "</question>"
    << ToXml(file.GetRating())
    << "<student_name>" << file.GetStudentName() << "</student_name>"
    << "<version>" << file.GetVersion() << "</version>"
    << "</file>"
  ;

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,6) == "<file>");
  assert(r.substr(r.size() - 7,7) == "</file>");
  return r;
}

ribi::braw::File ribi::braw::XmlToFile(const std::string& s)
{
  if ( !(s.size() >= 13)
    || s.substr(0,6) != "<file>"
    || s.substr(s.size() - 7,7) != "</file>"
  )
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "Cannot load XML different than '<file>[content]</file>', "
      << "received: '" << s << "'"
    ;
    throw std::invalid_argument(msg.str());
  }

  return File(
    ExtractFileAboutFromXml(s),
    ExtractFileAssessorNameFromXml(s),
    ExtractFileClusterFromXml(s),
    ExtractFileConceptMapFromXml(s),
    ExtractFileQuestionFromXml(s),
    ExtractFileRatingFromXml(s),
    ExtractFileStudentNameFromXml(s),
    ExtractFileVersionFromXml(s)
  );
}

bool ribi::braw::operator==(const File& lhs, const File& rhs) noexcept
{
  return
     lhs.GetAssessorName() == rhs.GetAssessorName()
  && lhs.GetCluster() == rhs.GetCluster()
  && lhs.GetConceptMap() == rhs.GetConceptMap()
  && lhs.GetRating() == rhs.GetRating()
  && lhs.GetStudentName() == rhs.GetStudentName()
  && lhs.GetVersion() == rhs.GetVersion();
}

bool ribi::braw::operator!=(const File& lhs, const File& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::braw::operator<<(std::ostream& os, const File& f) noexcept
{
  os << ToXml(f);
  return os;
}
