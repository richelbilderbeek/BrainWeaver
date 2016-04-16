#include "qtbrainweavermenudialog_test.h"

#include <boost/lexical_cast.hpp>

#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QLayout>
#include <QVBoxLayout>

#include "qtbrainweavermenudialog.h"
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

void ribi::pvdb::qtbrainweavermenudialog_test::press_all_buttons()
{
  QtPvdbMenuDialog d;
  d.show();
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
    QVERIFY(i < buttons.size());
    QPushButton * const button = buttons[i];
    QVERIFY(button);
    if (button->isEnabled()) button->click();
  }
}

void ribi::pvdb::qtbrainweavermenudialog_test::scenario_1()
{
  QtPvdbMenuDialog d;
  d.show();
  d.SetShowChildDialogsModal(false);
  Ui::QtPvdbMenuDialog * const ui = d.GetUi();
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
      QVERIFY(d.GetQuestion() == question);
      d.Save(filename);
    }
    //2) Load the assessor file (as a student)
    //3) Fill in a name
    {
      File file(LoadFile(filename));
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName().empty());
      QtPvdbStudentMenuDialog d(file);
      d.SetName(name);
      QVERIFY(d.GetName() == name);
      d.Save(filename);
    }
    //4) Start with concept map
    //5) Save
    #ifdef NOT_NOW_20141142
    {
      File file(File::Load(filename));
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName() == name);
      QtPvdbConceptMapDialog d(file);
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName() == name);
      QVERIFY(GetNodes(file.GetConceptMap()).size() == 1);
      QVERIFY(GetEdges(file.GetConceptMap()).empty());
      d.DoRandomStuff();
      QVERIFY(GetNodes(file.GetConceptMap()).size() > 1);
      QVERIFY(!GetEdges(file.GetConceptMap()).empty());
      d.Save(filename);
    }
    //6) Test if clustering is disabled
    {
      File file(File::Load(filename));
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName() == name);
      QVERIFY(GetNodes(file.GetConceptMap()).size() > 1);
      QVERIFY(!GetEdges(file.GetConceptMap()).empty());
      QVERIFY((file.GetCluster() || !file.GetCluster())
        && "If the file has no cluster, the cluster dialog creates it,"
        && "if no concept map was present");
      QtPvdbClusterDialog d(file);
      if (file.GetConceptMap() && !file.GetConceptMap())
      {
        QVERIFY(d.GetWidget());
        QVERIFY(!d.GetWidget()->isEnabled()
          && "Cluster widget should be disabled for a file with a filled in ConceptMap");
      }
    }
    #endif // NOT_NOW_20141142
    std::remove(File::GetTestFileName().c_str());
  }
}

void ribi::pvdb::qtbrainweavermenudialog_test::scenario_2()
{
  if (!"Fix issue #20") return;
  QtPvdbMenuDialog d;
  d.show();
  d.SetShowChildDialogsModal(false);
  Ui::QtPvdbMenuDialog * const ui = d.GetUi();
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
      QVERIFY(d.GetQuestion() == question);
      d.Save(filename);
    }
    //2) Load the assessor file (as a student)
    //3) Fill in a name
    {
      File file(LoadFile(filename));
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName().empty());
      QtPvdbStudentMenuDialog d(file);
      d.SetName(name);
      QVERIFY(d.GetName() == name);
      d.Save(filename);
    }
    //4) Start with clustering
    {
      File file(LoadFile(filename));
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName() == name);
      QtPvdbClusterDialog d(file);
      if (!boost::num_vertices(file.GetConceptMap()))
      {
        QVERIFY(!file.GetCluster().Empty() && "the cluster dialog used an existing or created a cluster");
      }
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName() == name);
      QVERIFY(!boost::num_vertices(file.GetConceptMap()));
      if (!file.GetCluster().Empty())
      {
        QVERIFY(d.GetWidget());
        d.DoRandomStuff();
      }
      QVERIFY(!boost::num_vertices(file.GetConceptMap()));
      d.Save(filename);
    }
    //5) Start with concept map
    //6) Save
    #ifdef NOT_NOW_20141142
    {
      File file(File::Load(filename));
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName() == name);
      QVERIFY(!boost::num_vertices(file.GetConceptMap()));
      QtPvdbConceptMapDialog d(file);
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName() == name);
      QVERIFY(file.GetConceptMap());
      d.DoRandomStuff();
      QVERIFY(GetNodes(file.GetConceptMap()).size() > 1);
      QVERIFY(!GetEdges(file.GetConceptMap()).empty());
      d.Save(filename);
    }
    //7) Test if clustering is disabled
    {
      File file(File::Load(filename));
      QVERIFY(file.GetQuestion() == question);
      QVERIFY(file.GetStudentName() == name);
      QVERIFY(GetNodes(file.GetConceptMap()).size() > 1);
      QVERIFY(!GetEdges(file.GetConceptMap()).empty());
      QVERIFY((file.GetCluster() || !file.GetCluster())
        && "If the file has no cluster, the cluster dialog creates it,"
           "if and only if there is no concept map");
      QtPvdbClusterDialog d(file);
      if (!file.GetConceptMap())
      {
        QVERIFY(file.GetCluster() && "the cluster dialog used an existing or created a cluster");
        QVERIFY(d.GetWidget());
        QVERIFY(!d.GetWidget()->isEnabled()
          && "Cluster widget should be disabled for a file with a filled in ConceptMap");
      }
    }
    #endif // NOT_NOW_20141142
    std::remove(File::GetTestFileName().c_str());
  }
}
