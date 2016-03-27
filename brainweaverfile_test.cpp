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


BOOST_AUTO_TEST_CASE(ribi_pvdb_file_test)
{
  using namespace ribi::pvdb;
  const std::string tmp_filename = ribi::pvdb::File::GetTempFileName();
  //Test copy constructor
  {
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
  //Test Save/Load on empty File
  {

    File firstfile;
    firstfile.Save(tmp_filename);
    const File secondfile = LoadFile(tmp_filename);
    BOOST_CHECK(firstfile == secondfile);
    //Modify f, to test operator!=
    firstfile.SetStudentName(firstfile.GetStudentName() + " (modified)");
    BOOST_CHECK(firstfile != secondfile);
  }
  //Test Save/Load on file
  {

    File firstfile;
    firstfile.SetStudentName("Richel Bilderbeek");
    const std::string question = "Focal question?";
    {
      const ribi::cmap::ConceptMap concept_map = CreateConceptMap(question);
      BOOST_CHECK(boost::num_vertices(concept_map) > 0);
      BOOST_CHECK(ribi::cmap::CountCenterNodes(concept_map) == 1);
      firstfile.SetConceptMap(concept_map);
    }
    firstfile.SetQuestion("Focal question?");
    BOOST_CHECK(firstfile.GetQuestion() == question);
    firstfile.Save(tmp_filename.c_str());
    BOOST_CHECK(firstfile.GetQuestion() == question);
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
  }
  //ISSUE 184 HERE
}
