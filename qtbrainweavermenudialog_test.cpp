#include "qtbrainweavermenudialog.h"
#include <boost/test/unit_test.hpp>

#include <boost/lexical_cast.hpp>

#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLayout>
#include <QVBoxLayout>

#include "add_custom_vertex.h"
#include "brainweaverfilefactory.h"
#include "brainweaverfile.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmapexamples.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnode.h"
#include "container.h"
#include "counter.h"
#include "fileio.h"
#include "plane.h"
#include "qtbrainweaveraboutdialog.h"
#include "qtbrainweaverassessormenudialog.h"
#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverclusterwidget.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweavercreateassessmentcompletedialog.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaveroverviewdialog.h"
#include "qtbrainweaverprintconceptmapdialog.h"
#include "qtbrainweaverprintratingdialog.h"
#include "qtbrainweaverrateconceptmapdialog.h"
#include "qtbrainweaverratingdialog.h"
#include "qtbrainweaverstudentmenudialog.h"
#include "qtbrainweavertestcreatesubconceptmapdialog.h"
#include "qtbrainweaverviewfilesdialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmaprateconceptdialognewname.h"
#include "qtconceptmaprateconcepttallydialognewname.h"
#include "qtconceptmaprateexamplesdialognewname.h"
//#include "qtconceptmapviewtestsdialog.h"
#include "qtstylesheetsettermaindialog.h"
#include "qttestconceptmapmenudialog.h"
#include "qttesteditconceptmapdialog.h"
#include "qttestqtarrowitemsmenudialog.h"
#include "qttestqtroundededitrectitemmenudialog.h"
#include "qttestqtroundedrectitemmenudialog.h"
#include "ribi_regex.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtbrainweavermenudialog.h"

BOOST_AUTO_TEST_CASE(ribi_pvdb_qtmenudialog_test)
{
  using namespace ribi::pvdb;
  //Press all buttons
  {
    QtPvdbMenuDialog d;
    d.SetShowChildDialogsModal(false);
    Ui::QtPvdbMenuDialog * const ui = d.GetUi();
    const std::vector<QPushButton*> buttons
      =
      {
        //Duplication of tests, the ones I am most interested in now

        //Normal alphabetical order of tests
        ui->button_about,
        ui->button_assessor,
        ui->button_create_test_files,
        ui->button_modify_stylesheet,
        ui->button_overview,
        ui->button_print_concept_map,
        ui->button_print_rating,
        ui->button_rate_concept,
        ui->button_rate_concept_auto,
        ui->button_rate_concept_map,
        ui->button_rate_examples,
        ui->button_rating,
        ui->button_student,
        ui->button_test_arrowitems,
        ui->button_test_cluster,
        ui->button_test_conceptmap,
        ui->button_test_create_sub_concept_map,
        ui->button_test_conceptmaps,
        ui->button_test_qtroundededitrectitem,
        ui->button_view_files
      };
    const std::size_t n_buttons = buttons.size();
    for (std::size_t i = 0; i!=n_buttons; ++i)
    {
      BOOST_CHECK(i < buttons.size());
      QPushButton * const button = buttons[i];
      BOOST_CHECK(button);
      if (button->isEnabled()) button->click();
    }

  }
  //THE MULTI DIALOG TESTS HERE
  //MULTI DIALOG TEST #1
  //1) Create an assessor question file
  //2) Load the assessor file (as a student)
  //3) Fill in a name
  //4) Start with concept map
  //5) Save
  //6) Test if clustering is disabled
  {
    const std::string question = "DEBUG_QUESTION";
    const std::string filename = File::GetTestFileName();
    const std::string name = "DEBUG_NAME";
    //1) Create an assessor question file
    {
      QtPvdbCreateAssessmentCompleteDialog d;
      d.SetQuestion(question);
      BOOST_CHECK(d.GetQuestion() == question);
      d.Save(filename);
    }
    //2) Load the assessor file (as a student)
    //3) Fill in a name
    {
      File file(LoadFile(filename));
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName().empty());
      QtPvdbStudentMenuDialog d(file);
      d.SetName(name);
      BOOST_CHECK(d.GetName() == name);
      d.Save(filename);
    }
    //4) Start with concept map
    //5) Save
    #ifdef NOT_NOW_20141142
    {
      File file(File::Load(filename));
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName() == name);
      QtPvdbConceptMapDialog d(file);
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName() == name);
      BOOST_CHECK(GetNodes(file.GetConceptMap()).size() == 1);
      BOOST_CHECK(GetEdges(file.GetConceptMap()).empty());
      d.DoRandomStuff();
      BOOST_CHECK(GetNodes(file.GetConceptMap()).size() > 1);
      BOOST_CHECK(!GetEdges(file.GetConceptMap()).empty());
      d.Save(filename);
    }
    //6) Test if clustering is disabled
    {
      File file(File::Load(filename));
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName() == name);
      BOOST_CHECK(GetNodes(file.GetConceptMap()).size() > 1);
      BOOST_CHECK(!GetEdges(file.GetConceptMap()).empty());
      BOOST_CHECK((file.GetCluster() || !file.GetCluster())
        && "If the file has no cluster, the cluster dialog creates it,"
        && "if no concept map was present");
      QtPvdbClusterDialog d(file);
      if (file.GetConceptMap() && !file.GetConceptMap())
      {
        BOOST_CHECK(d.GetWidget());
        BOOST_CHECK(!d.GetWidget()->isEnabled()
          && "Cluster widget should be disabled for a file with a filled in ConceptMap");
      }
    }
    #endif // NOT_NOW_20141142
    std::remove(File::GetTestFileName().c_str());
  }
  //Long test #2
  //1) Create an assessor question file
  //2) Load the assessor file (as a student)
  //3) Fill in a name
  //4) Start with clustering
  //5) Start with concept map
  //6) Save
  {
    const std::string question = "DEBUG_QUESTION";
    const std::string filename = File::GetTestFileName();
    const std::string name = "DEBUG_NAME";
    //1) Create an assessor question file
    {
      QtPvdbCreateAssessmentCompleteDialog d;
      d.SetQuestion(question);
      BOOST_CHECK(d.GetQuestion() == question);
      d.Save(filename);
    }
    //2) Load the assessor file (as a student)
    //3) Fill in a name
    {
      File file(LoadFile(filename));
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName().empty());
      QtPvdbStudentMenuDialog d(file);
      d.SetName(name);
      BOOST_CHECK(d.GetName() == name);
      d.Save(filename);
    }
    //4) Start with clustering
    {
      File file(LoadFile(filename));
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName() == name);
      QtPvdbClusterDialog d(file);
      if (!boost::num_vertices(file.GetConceptMap()))
      {
        BOOST_CHECK(!file.GetCluster().Empty() && "the cluster dialog used an existing or created a cluster");
      }
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName() == name);
      BOOST_CHECK(!boost::num_vertices(file.GetConceptMap()));
      if (!file.GetCluster().Empty())
      {
        BOOST_CHECK(d.GetWidget());
        d.DoRandomStuff();
      }
      BOOST_CHECK(!boost::num_vertices(file.GetConceptMap()));
      d.Save(filename);
    }
    //5) Start with concept map
    //6) Save
    #ifdef NOT_NOW_20141142
    {
      File file(File::Load(filename));
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName() == name);
      BOOST_CHECK(!boost::num_vertices(file.GetConceptMap()));
      QtPvdbConceptMapDialog d(file);
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName() == name);
      BOOST_CHECK(file.GetConceptMap());
      d.DoRandomStuff();
      BOOST_CHECK(GetNodes(file.GetConceptMap()).size() > 1);
      BOOST_CHECK(!GetEdges(file.GetConceptMap()).empty());
      d.Save(filename);
    }
    //7) Test if clustering is disabled
    {
      File file(File::Load(filename));
      BOOST_CHECK(file.GetQuestion() == question);
      BOOST_CHECK(file.GetStudentName() == name);
      BOOST_CHECK(GetNodes(file.GetConceptMap()).size() > 1);
      BOOST_CHECK(!GetEdges(file.GetConceptMap()).empty());
      BOOST_CHECK((file.GetCluster() || !file.GetCluster())
        && "If the file has no cluster, the cluster dialog creates it,"
           "if and only if there is no concept map");
      QtPvdbClusterDialog d(file);
      if (!file.GetConceptMap())
      {
        BOOST_CHECK(file.GetCluster() && "the cluster dialog used an existing or created a cluster");
        BOOST_CHECK(d.GetWidget());
        BOOST_CHECK(!d.GetWidget()->isEnabled()
          && "Cluster widget should be disabled for a file with a filled in ConceptMap");
      }
    }
    #endif // NOT_NOW_20141142
    std::remove(File::GetTestFileName().c_str());
  }

}
