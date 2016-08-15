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
  using namespace ribi::braw;
  File f;
  f.SetAssessorName("debug assessor name");
  f.SetStudentName("debug student name");
  File g = f;
  BOOST_CHECK_EQUAL(f, g);
  //Modify g, to test operator!=
  g.SetStudentName( f.GetStudentName() + " (modified with spaces)");
  BOOST_CHECK_NE(f, g);
  g.SetStudentName( f.GetStudentName());
  BOOST_CHECK_EQUAL(f, g);
  g.SetAssessorName( f.GetAssessorName() + " (modified with spaces)");
  BOOST_CHECK_NE(f, g);
  g.SetAssessorName( f.GetAssessorName());
  BOOST_CHECK_EQUAL(f, g);
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_setquestion_and_getquestion_are_symmetric)
{
  ribi::braw::File f;
  const std::string question{"Question with space"};
  BOOST_CHECK_NE(f.GetQuestion(), question);
  f.SetQuestion(question);
  BOOST_CHECK_EQUAL(f.GetQuestion(), question);
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_setstudentname_and_getstudentname_are_symmetric)
{
  ribi::braw::File f;
  const std::string studentname{"Student name"};
  BOOST_CHECK_NE(f.GetStudentName(), studentname);
  f.SetStudentName(studentname);
  BOOST_CHECK_EQUAL(f.GetStudentName(), studentname);
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_rejects_empty_concept_map)
{
  ribi::braw::File file;
  ribi::cmap::ConceptMap g;
  BOOST_CHECK_THROW(
    file.SetConceptMap(g),
    std::invalid_argument
  );
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_rejects_concept_map_without_center_nodes)
{
  ribi::braw::File file;
  ribi::cmap::ConceptMap g;
  const auto n = ribi::cmap::Node(ribi::cmap::Concept("question with spaces"), false);
  assert(!n.IsCenterNode());
  add_custom_and_selectable_vertex(n,false,g);
  BOOST_CHECK_THROW(
    file.SetConceptMap(g),
    std::invalid_argument
  );
}


BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_rejects_concept_map_with_two_center_nodes)
{
  ribi::braw::File file;
  ribi::cmap::ConceptMap g;
  const auto n = ribi::cmap::Node(ribi::cmap::Concept("question with spaces"), true);
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
  ribi::braw::File file;
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
  const std::string question{"question with spaces"};
  ribi::braw::File file;
  file.SetQuestion(question);
  ribi::cmap::ConceptMap g;
  const auto node = ribi::cmap::Node(ribi::cmap::Concept(question), true);
  assert(node.IsCenterNode());
  add_custom_and_selectable_vertex(node,false,g);
  BOOST_CHECK_NO_THROW(file.SetConceptMap(g));
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_CreateConceptMap)
{
  const ribi::cmap::ConceptMap concept_map = ribi::braw::CreateConceptMap("some question");
  BOOST_CHECK(boost::num_vertices(concept_map) > 0);
  BOOST_CHECK_EQUAL(ribi::cmap::CountCenterNodes(concept_map), 1);
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_save_and_load_empty_file)
{
  using namespace ribi::braw;
  const std::string tmp_filename = ribi::braw::File::GetTempFileName();
  //Test Save/Load on empty File
  File first_file;
  first_file.Save(tmp_filename);
  const File secondfile = LoadFile(tmp_filename);
  BOOST_CHECK_EQUAL(first_file, secondfile);
  //Modify f, to test operator!=
  first_file.SetStudentName(first_file.GetStudentName() + " (modified)");
  BOOST_CHECK_NE(first_file, secondfile);
  std::remove(tmp_filename.c_str());
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_cannot_load_nonexisting_file)
{
  const std::string tmp_filename = ribi::get_temp_filename(".txt");
  assert(!is_regular_file(tmp_filename));
  BOOST_CHECK_THROW(ribi::braw::LoadFile(tmp_filename), std::invalid_argument)
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_cannot_load_gibberish)
{
  const std::string tmp_filename = ribi::get_temp_filename(".txt");
  { std::ofstream f(tmp_filename); f << "gibberish"; }
  assert(is_regular_file(tmp_filename));
  BOOST_CHECK_THROW(ribi::braw::LoadFile(tmp_filename), std::invalid_argument)
  std::remove(tmp_filename.c_str());
}


BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_save_and_load_normal_file)
{
  //Test Save/Load on file
  using namespace ribi::braw;
  const std::string filename{"test_ribi_pvdb_file_save_and_load_normal_file.cmp"};
  File first_file;
  first_file.SetStudentName("Richel Bilderbeek");
  const std::string question = "Focal question?";
  first_file.SetQuestion(question);
  const ribi::cmap::ConceptMap concept_map = CreateConceptMap(question);

  BOOST_CHECK_EQUAL(GetFirstNode(concept_map).GetName(), question);

  first_file.SetConceptMap(concept_map);
  BOOST_CHECK_EQUAL(GetFirstNode(first_file.GetConceptMap()).GetName(), question);

  first_file.Save(filename.c_str());

  BOOST_CHECK_EQUAL(GetFirstNode(first_file.GetConceptMap()).GetName(), question);

  const File second_file = LoadFile(filename);
  BOOST_REQUIRE_EQUAL(
    boost::num_vertices(first_file.GetConceptMap()),
    boost::num_vertices(second_file.GetConceptMap())
  );


  BOOST_CHECK_EQUAL(second_file.GetQuestion(), first_file.GetQuestion());
  BOOST_TEST_PASSPOINT();
  BOOST_CHECK_EQUAL(GetFirstNode(second_file.GetConceptMap()).GetName(), question);
  BOOST_TEST_PASSPOINT();
  BOOST_CHECK_EQUAL(first_file, second_file);
  BOOST_TEST_PASSPOINT();
  //Modify f, to test operator!=
  first_file.SetStudentName( first_file.GetStudentName() + " (modified)");
  BOOST_CHECK_NE(first_file, second_file);
  std::remove(filename.c_str());
}

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_file_save_and_load_all_testing_files)
{
  const std::vector<ribi::braw::File> files = ribi::braw::FileFactory().GetTests();
  for(const auto& file: files)
  {
    const std::string filename = "test_ribi_pvdb_file_save_and_load_all_testing_files.cmp";
    file.Save(filename);
    assert(is_regular_file(filename));
    const auto file_again = ribi::braw::LoadFile(filename);
    BOOST_CHECK_EQUAL (file, file_again);
    ribi::FileIo().DeleteFile(filename);
  }
}
