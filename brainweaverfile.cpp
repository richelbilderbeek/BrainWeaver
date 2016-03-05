//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2013-2016 The Brainweaver Team

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
#include "brainweaverfile.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <QFile>
#include <QRegExp>

#include "counter.h"
#include "conceptmapregex.h"
#include "conceptmapcenternodefactory.h"

#include "add_custom_vertex.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnode.h"
#include "fileio.h"
#include "brainweaverclusterfactory.h"
#include "brainweavercluster.h"
#include "brainweaverfilefactory.h"
#include "brainweaverhelper.h"
#include "brainweaverregex.h"
#include "ribi_regex.h"
#include "testtimer.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

const std::string ribi::pvdb::File::m_filename_extension = "cmp";

ribi::pvdb::File::File()
  : m_about("Brainweaver"),
    m_assessor_name(""),
    m_cluster{},
    m_concept_map(), //nullptr
    m_question(""),
    m_student_name(""),
    m_version("0.4")
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::pvdb::File::File(
  const std::string& about,
  const std::string& assessor_name,
  const Cluster& cluster,
  const ribi::cmap::ConceptMap& concept_map,
  const std::string& question,
  const std::string& student_name,
  const std::string& version)
  : m_about(about),
    m_assessor_name(assessor_name),
    m_cluster(cluster),
    m_concept_map(concept_map),
    m_question(question),
    m_student_name(student_name),
    m_version(version)
{
  #ifndef NDEBUG
  Test();
  #endif
}

void ribi::pvdb::File::AutoSave() const
{
  this->Save("autosave1." + m_filename_extension);
  this->Save("autosave2." + m_filename_extension);
}

std::string ribi::pvdb::File::GetQuestion() const
{
  return m_question;
}

std::string ribi::pvdb::File::GetTempFileName()
{
  return "tmp." + m_filename_extension;
}

std::string ribi::pvdb::File::GetTestFileName()
{
  return "test." + m_filename_extension;
}

std::vector<ribi::pvdb::File> ribi::pvdb::File::GetTests() noexcept
{
  std::vector<File> v;
  const int n_clusters{ClusterFactory().GetNumberOfTests()};
  const int n_concept_maps{cmap::ConceptMapFactory().GetNumberOfAllTests()};
  for (int cluster_index=0; cluster_index!=n_clusters; ++cluster_index)
  {
    for (int concept_map_index=0; concept_map_index!=n_concept_maps; ++concept_map_index)
    {
      const std::string about = "about";
      const std::string assessor_name = "assessor_name";
      std::string question = "question";
      const std::string student_name = "student_name";
      const std::string version = "version";
      const auto cluster = pvdb::ClusterFactory().GetTests()[cluster_index];
      const auto concept_map = ribi::cmap::ConceptMapFactory().GetAllTests()[concept_map_index];
      File file(
        about,
        assessor_name,
        cluster,
        concept_map,
        question,
        student_name,
        version
      );
      v.push_back(file);
    }
  }
  return v;
}

ribi::pvdb::File ribi::pvdb::File::Load(const std::string &filename)
{
  std::string xml;
  //Read XML from file
  {
    const std::vector<std::string> v = pvdb::SafeFileToVector(filename);
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

  File file = ribi::pvdb::XmlToFile(xml);

  //assert( (!file.GetConceptMap() || !GetNodes(file.GetConceptMap()).empty() ) //TODO RJCB: Put back in
  //  && "Either a file has no concept map or it has at least one node"); //TODO RJCB: Put back in
  //assert( (!file.GetConceptMap() || file.GetConceptMap().FindCenterNode()) //TODO RJCB: Put back in
  //  && "Either a file has no concept map or the file's ConceptMap has a CenterNode"); //TODO RJCB: Put back in

  return file;
}

void ribi::pvdb::File::Save(const std::string &filename) const
{
  //Check for correct extension
  if (!(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == m_filename_extension))
  {
    TRACE(filename);
  }
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == m_filename_extension
    && "File must have correct file extension name"
  );
  {
    std::ofstream f(filename.c_str());
    const std::string s = ToXml(*this);
    f << s;
  }
  #ifndef NDEBUG
  //Check if load results in the same File
  {
    const std::vector<std::string> v = pvdb::SafeFileToVector(filename);
    if (v.empty()) { TRACE(v.size()); TRACE(filename); }
    assert(!v.empty() && "File must not be empty");
  }
  #endif
}

void ribi::pvdb::File::SetAssessorName(const std::string& assessor_name)
{
  assert(assessor_name.size() > 1);
  m_assessor_name = assessor_name;
  this->AutoSave();
}

void ribi::pvdb::File::SetConceptMap(const ribi::cmap::ConceptMap& concept_map)
{
  m_concept_map = concept_map;
  //assert(m_concept_map->GetNodes().empty() //TODO: put back in
  //  && "In Brainweaver, every ConceptMap must have at least one node");
  //assert(m_concept_map->FindCenterNode() //TODO RJCB: to put back in
  //  && "In Brainweaver, every ConceptMap must have a CenterNode"); //TODO RJCB: to put back in
  this->AutoSave();
}

void ribi::pvdb::File::SetCluster(const Cluster& cluster) noexcept
{
  //Don't care: m_cluster will be overwritten more often,
  //because the TreeWidget has no Model/View architecture: the resulting
  //cluster is allocated new and calculated every save
  //assert(!m_cluster);

  m_cluster = cluster;
  this->AutoSave();
}

void ribi::pvdb::File::SetQuestion(const std::string& question)
{
  assert(question.size() > 0);
  m_question = question;
  this->AutoSave();
}

void ribi::pvdb::File::SetStudentName(const std::string& student_name)
{
  assert(student_name.size() > 1);
  m_student_name = student_name;
  this->AutoSave();
}

#ifndef NDEBUG
void ribi::pvdb::File::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Counter();
    ribi::fileio::FileIo();
    ribi::Regex();
    ribi::pvdb::Regex();
    ribi::cmap::Regex();
    CreateConceptMap("Focal question?");
    ClusterFactory();
    ClusterFactory().GetTest( {0} );
  }
  const TestTimer test_timer(__func__,__FILE__,2.0);
  const std::string tmp_filename = ribi::pvdb::File::GetTempFileName();
  //Test copy constructor
  {
    File f;
    f.SetAssessorName("debug assessor name");
    f.SetStudentName("debug student name");
    File g = f;
    assert(f == g);
    //Modify g, to test operator!=
    g.SetStudentName( f.GetStudentName() + " (modified)");
    assert(f != g);
    g.SetStudentName( f.GetStudentName());
    assert(f == g);
    g.SetAssessorName( f.GetAssessorName() + " (modified)");
    assert(f != g);
    g.SetAssessorName( f.GetAssessorName());
    assert(f == g);
  }
  //Test Save/Load on empty File
  {

    File firstfile;
    firstfile.Save(tmp_filename);
    const File secondfile = File::Load(tmp_filename);
    assert(firstfile == secondfile);
    //Modify f, to test operator!=
    firstfile.SetStudentName(firstfile.GetStudentName() + " (modified)");
    assert(firstfile != secondfile);
  }
  //Test Save/Load on file
  {

    File firstfile;
    firstfile.SetStudentName("Richel Bilderbeek");
    const std::string question = "Focal question?";
    {
      const ribi::cmap::ConceptMap concept_map = CreateConceptMap(question);
      assert(boost::num_vertices(concept_map) > 0);
      assert(ribi::cmap::CountCenterNodes(concept_map) == 1);
      firstfile.SetConceptMap(concept_map);
    }
    firstfile.SetQuestion("Focal question?");
    assert(firstfile.GetQuestion() == question);
    firstfile.Save(tmp_filename.c_str());
    assert(firstfile.GetQuestion() == question);
    const File second_file(File::Load(tmp_filename));
    assert(second_file.GetQuestion() == firstfile.GetQuestion());
    if (firstfile != second_file)
    {
      TRACE(firstfile);
      TRACE(second_file);
    }
    assert(firstfile == second_file);
    //Modify f, to test operator!=
    firstfile.SetStudentName( firstfile.GetStudentName() + " (modified)");
    assert(firstfile != second_file);
  }
  {

    ///Continue loop until no file is found
    for (int i=0; i!=100; ++i)
    {
      //Testing filenames start at 1
      const std::string filename = boost::lexical_cast<std::string>(i) + ".cmp";
      if (!fileio::FileIo().IsRegularFile(filename))
      {
        //Copy the file from Qt resources to local file
        {
          const std::string qtfilename = ":/files/" + filename;
          QFile qtfile(qtfilename.c_str());
          qtfile.copy(filename.c_str());
          qtfile.close();
        }
        if (!fileio::FileIo().IsRegularFile(filename))
        {
          //TRACE("First filename not found: ");
          //TRACE(filename);
          continue;
        }

        QFile file(filename.c_str());

        const bool success = file.setPermissions(
            QFile::ReadOwner
          | QFile::WriteOwner
          | QFile::ExeOwner
          | QFile::ReadUser
          | QFile::WriteUser
          | QFile::ExeUser
          | QFile::ReadGroup
          | QFile::WriteGroup
          | QFile::ExeGroup
          | QFile::ReadOther
          | QFile::WriteOther
          | QFile::ExeOther
          );
        assert(success);
        ribi::pvdb::File::Load(filename);
        std::remove(filename.c_str());
      }
    }
  }
  //ISSUE 184 HERE
}
#endif

ribi::cmap::ConceptMap ribi::pvdb::CreateConceptMap(
  const std::string& text) noexcept
{
  ribi::cmap::ConceptMap g;
  ribi::cmap::Node n(ribi::cmap::Concept(text),true);
  add_custom_vertex(n, g);
  assert(ribi::cmap::CountCenterNodes(g) == 1 && "A Brainweaver ConceptMap must have a CenterNode");
  return g;
}

std::string ribi::pvdb::DoXpressiveRegexReplace(
  const std::string& str,
  const std::string& regex_str,
  const std::string& format_str
) noexcept
{
  try
  {
    return boost::xpressive::regex_replace(
      str,
      boost::xpressive::sregex(boost::xpressive::sregex::compile(regex_str)),
      format_str,
      boost::xpressive::regex_constants::match_default
        | boost::xpressive::regex_constants::format_all
        | boost::xpressive::regex_constants::format_no_copy);
  }
  catch (boost::xpressive::regex_error& e)
  {
    const std::string s
      = "boost::xpressive::regex_error: " + std::string(e.what());
    TRACE(str);
    TRACE(regex_str);
    TRACE(format_str);
    TRACE(s);
    assert(!"Should not get here");
    throw std::logic_error(s.c_str());
  }
}

std::string ribi::pvdb::FileToStr(const std::string& filename) noexcept
{
  assert(fileio::FileIo().IsRegularFile(filename.c_str()));
  std::string s;
  std::ifstream in(filename.c_str());
  while (!in.eof())
  {
    std::string t;
    std::getline(in,t);
    s+=t;
  }
  return s;
}

std::string ribi::pvdb::ToXml(const File& file) noexcept
{
  //assert(file.m_cluster);
  //assert(file.m_concept_map);

  std::stringstream s;
  s << "<file>";
  s << "<about>" << file.GetAbout() << "</about>";
  s << "<assessor_name>" << file.GetAssessorName() << "</assessor_name>";
  s << Cluster::ToXml(file.GetCluster());
  s << ribi::cmap::ToXml(file.GetConceptMap());
  s << "<question>" << file.GetQuestion() << "</question>";
  s << "<student_name>" << file.GetStudentName() << "</student_name>";
  s << "<version>" << file.GetVersion() << "</version>";
  s << "</file>";

  const std::string r = s.str();
  assert(r.size() >= 13);
  assert(r.substr(0,6) == "<file>");
  assert(r.substr(r.size() - 7,7) == "</file>");

  return r;
}

ribi::pvdb::File ribi::pvdb::XmlToFile(const std::string& s)
{
  assert(s.size() >= 13);
  assert(s.substr(0,6) == "<file>");
  assert(s.substr(s.size() - 7,7) == "</file>");

  std::string about;
  std::string assessor_name;
  Cluster cluster;
  ribi::cmap::ConceptMap concept_map;
  std::string question;
  std::string student_name;
  std::string version;
  //m_about_str
  {
    const std::vector<std::string> v
      = pvdb::GetRegexMatches(s,QRegExp("(<about>.*</about>)"));
    assert(v.size() == 1);
    about = ribi::xml::StripXmlTag(v[0]);
  }
  //m_assessor_name
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<assessor_name>.*</assessor_name>)"));
    assert(v.size() == 1);
    assessor_name = ribi::xml::StripXmlTag(v[0]);
  }
  //m_cluster
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<cluster>.*</cluster>)"));
    if (!v.empty())
    {
      assert(v.size() == 1);
      cluster = Cluster::FromXml(v[0]);
    }
    else
    {
      //No cluster yet
    }
  }
  //m_concept_map
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<concept_map>.*</concept_map>)"));
    if (!v.empty())
    {
      assert(v.size() == 1);
      concept_map = ribi::cmap::XmlToConceptMap(v[0]);
    }
    else
    {
      //No concept map yet
    }
  }
  //m_question
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<question>.*</question>)"));
    if (v.empty())
    {
      std::clog << "Warning: no question supplied" << std::endl;
      question = "";
    }
    else
    {
      question = ribi::xml::StripXmlTag(v[0]);
    }
  }
  //m_student_name
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<student_name>.*</student_name>)"));
    assert(v.size() == 1);
    student_name = ribi::xml::StripXmlTag(v[0]);
  }
  //m_version
  {
    const std::vector<std::string> v = pvdb::GetRegexMatches(s,QRegExp("(<version>.*</version>)"));
    assert(v.size() == 1);
    version = ribi::xml::StripXmlTag(v[0]);
  }

  //assert( (!f->GetConceptMap() || !f->GetConceptMap().GetNodes().empty() ) //TODO RJCB: Put back in
  //  && "Either a file has no concept map or it has at least one node"); //TODO RJCB: Put back in
  //assert( (!f->GetConceptMap() || f->GetConceptMap().FindCenterNode() ) //TODO RJCB: Put back in
  //  && "Either a file has no concept map or the first node in a file's ConceptMap is be a CenterNode"); //TODO RJCB: Put back in

  return File(
    about,
    assessor_name,
    cluster,
    concept_map,
    question,
    student_name,
    version
  );
}

bool ribi::pvdb::operator==(const pvdb::File& lhs, const pvdb::File& rhs) noexcept
{
  return
     lhs.GetAssessorName() == rhs.GetAssessorName()
  && lhs.GetCluster() == rhs.GetCluster()
  && lhs.GetConceptMap() == rhs.GetConceptMap()
  && lhs.GetStudentName() == rhs.GetStudentName()
  && lhs.GetVersion() == rhs.GetVersion();
}

bool ribi::pvdb::operator!=(const pvdb::File& lhs, const pvdb::File& rhs) noexcept
{
  return !(lhs == rhs);
}

std::ostream& ribi::pvdb::operator<<(std::ostream& os, const ribi::pvdb::File& f) noexcept
{
  os << ToXml(f);
  return os;
}
