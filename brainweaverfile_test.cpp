#include "brainweaverfile.h"
#include <boost/test/unit_test.hpp>

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
#include "is_regular_file.h"
#include "add_custom_and_selectable_vertex.h"
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


BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_copy_constructor)
{
  using namespace ribi::pvdb;
  File f;
  f.SetAssessorName("debug assessor name");
  f.SetStudentName("debug student name");
  File g = f;
  BOOST_CHECK(f == g);
  //Modify g, to test operator!=
  g.SetStudentName( f.GetStudentName() + " (modified)");
  BOOST_CHECK(f != g);
  g.SetStudentName( f.GetStudentName());
  BOOST_CHECK(f == g);
  g.SetAssessorName( f.GetAssessorName() + " (modified)");
  BOOST_CHECK(f != g);
  g.SetAssessorName( f.GetAssessorName());
  BOOST_CHECK(f == g);
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_setquestion_and_getquestion_are_symmetric)
{
  ribi::pvdb::File f;
  const std::string question{"Question"};
  BOOST_CHECK(f.GetQuestion() != question);
  f.SetQuestion(question);
  BOOST_CHECK(f.GetQuestion() == question);
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_setstudentname_and_getstudentname_are_symmetric)
{
  ribi::pvdb::File f;
  const std::string studentname{"Question"};
  BOOST_CHECK(f.GetStudentName() != studentname);
  f.SetStudentName(studentname);
  BOOST_CHECK(f.GetStudentName() == studentname);
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_rejects_empty_concept_map)
{
  ribi::pvdb::File file;
  ribi::cmap::ConceptMap g;
  BOOST_CHECK_THROW(
    file.SetConceptMap(g),
    std::invalid_argument
  );
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_rejects_concept_map_without_center_nodes)
{
  ribi::pvdb::File file;
  ribi::cmap::ConceptMap g;
  const auto n = ribi::cmap::Node(ribi::cmap::Concept("question"), false);
  assert(!n.IsCenterNode());
  add_custom_and_selectable_vertex(n,false,g);
  BOOST_CHECK_THROW(
    file.SetConceptMap(g),
    std::invalid_argument
  );
}


BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_rejects_concept_map_with_two_center_nodes)
{
  ribi::pvdb::File file;
  ribi::cmap::ConceptMap g;
  const auto n = ribi::cmap::Node(ribi::cmap::Concept("question"), true);
  assert(n.IsCenterNode());
  add_custom_and_selectable_vertex(n,false,g);
  add_custom_and_selectable_vertex(n,false,g);
  BOOST_CHECK_THROW(
    file.SetConceptMap(g),
    std::invalid_argument
  );
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_rejects_concept_map_with_center_node_with_text_different_than_question)
{
  ribi::pvdb::File file;
  ribi::cmap::ConceptMap g;
  const std::string file_question{"File question"};
  const std::string text_on_center_node{"Text on center node"};
  file.SetQuestion(file_question);
  const auto n = ribi::cmap::Node(ribi::cmap::Concept(text_on_center_node), true);
  assert(n.IsCenterNode());
  add_custom_and_selectable_vertex(n,false,g);
  BOOST_CHECK_THROW(file.SetConceptMap(g), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_accepts_concept_map_with_center_node)
{
  const std::string question{"question"};
  ribi::pvdb::File file;
  file.SetQuestion(question);
  ribi::cmap::ConceptMap g;
  const auto node = ribi::cmap::Node(ribi::cmap::Concept(question), true);
  assert(node.IsCenterNode());
  add_custom_and_selectable_vertex(node,false,g);
  BOOST_CHECK_NO_THROW(file.SetConceptMap(g));
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_CreateConceptMap)
{
  const ribi::cmap::ConceptMap concept_map = ribi::pvdb::CreateConceptMap("some question");
  BOOST_CHECK(boost::num_vertices(concept_map) > 0);
  BOOST_CHECK(ribi::cmap::CountCenterNodes(concept_map) == 1);
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_save_and_load_empty_file)
{
  using namespace ribi::pvdb;
  const std::string tmp_filename = ribi::pvdb::File::GetTempFileName();
  //Test Save/Load on empty File
  File firstfile;
  firstfile.Save(tmp_filename);
  const File secondfile = LoadFile(tmp_filename);
  BOOST_CHECK(firstfile == secondfile);
  //Modify f, to test operator!=
  firstfile.SetStudentName(firstfile.GetStudentName() + " (modified)");
  BOOST_CHECK(firstfile != secondfile);
  std::remove(tmp_filename.c_str());
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_cannot_load_nonexisting_file)
{
  const std::string tmp_filename = ribi::pvdb::File::GetTempFileName();
  assert(!is_regular_file(tmp_filename));
  BOOST_CHECK_THROW(ribi::pvdb::LoadFile(tmp_filename), std::invalid_argument)
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_cannot_load_gibberish)
{
  const std::string tmp_filename = ribi::pvdb::File::GetTempFileName();
  { std::ofstream f(tmp_filename); f << "gibberish"; }
  assert(is_regular_file(tmp_filename));
  BOOST_CHECK_THROW(ribi::pvdb::LoadFile(tmp_filename), std::invalid_argument)
  std::remove(tmp_filename.c_str());
}


BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_save_and_load_normal_file)
{
  //Test Save/Load on file
  using namespace ribi::pvdb;
  File firstfile;
  firstfile.SetStudentName("Richel Bilderbeek");
  const std::string question = "Focal question?";
  firstfile.SetQuestion(question);
  const ribi::cmap::ConceptMap concept_map = CreateConceptMap(question);

  firstfile.SetConceptMap(concept_map);

  const std::string tmp_filename = ribi::pvdb::File::GetTempFileName();
  firstfile.Save(tmp_filename.c_str());

  const File second_file = LoadFile(tmp_filename);

  BOOST_CHECK(second_file.GetQuestion() == firstfile.GetQuestion());
  if (firstfile != second_file)
  {
    TRACE(firstfile);
    TRACE(second_file);
  }
  BOOST_CHECK(firstfile == second_file);
  //Modify f, to test operator!=
  firstfile.SetStudentName( firstfile.GetStudentName() + " (modified)");
  BOOST_CHECK(firstfile != second_file);
  std::remove(tmp_filename.c_str());
}


BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_issue_184)
{
  //ISSUE 184 HERE
}
