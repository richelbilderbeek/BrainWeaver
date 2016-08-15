#include "qtbrainweaverconceptmapdialog_test.h"

#include "is_custom_vertices_isomorphic.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "conceptmapcenternodefactory.h"
#include "add_custom_and_selectable_vertex.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmaphelper.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "brainweaverclusterfactory.h"
#include "brainweavercluster.h"
#include "brainweaverfile.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmapqtedge.h"

#include "qtconceptmap.h"
#include "qtconceptmapqtnode.h"
#include "testtimer.h"
#include "trace.h"

void ribi::braw::qtbrainweaverconceptmapdialog_test::a_file_its_conceptmap_must_have_a_center_node()
{
  //If this dialog is fed with a file with only a focal question, it will create a one-node concept map
  try
  {
    const std::string question = "TESTQUESTION";
    File file;
    file.SetQuestion(question);
    QVERIFY(file.GetCluster().Empty());
    QVERIFY(!boost::num_vertices(file.GetConceptMap()));

    ribi::cmap::ConceptMap concept_map;
    add_custom_and_selectable_vertex(
      ribi::cmap::Node(ribi::cmap::Concept(question), true),false,concept_map);
    QVERIFY(boost::num_vertices(concept_map) > 0);
    file.SetConceptMap(concept_map);
    QVERIFY(file.GetQuestion() == question);
    QVERIFY(boost::num_vertices(file.GetConceptMap()));
    QVERIFY(!GetNodes(file.GetConceptMap()).empty());
    QVERIFY(HasCenterNode(file.GetConceptMap()));
    const QtConceptMapDialog d(file);
    assert(d.GetWidget());
    QVERIFY(boost::num_vertices(d.GetWidget()->GetConceptMap()) == 1);
  }
  catch (std::exception& e)
  {
    qDebug() << e.what();
    QVERIFY(!"Should not get here");
  }
}

void ribi::braw::qtbrainweaverconceptmapdialog_test::create_from_cluster()
{
  const std::string question = "TESTQUESTION";
  ribi::braw::Cluster cluster(
    {
      ribi::cmap::Concept("name 1"),
      ribi::cmap::Concept("name 2"),
      ribi::cmap::Concept("name 3")
    }
  );
  const auto concept_map = CreateFromCluster(question,cluster);
  const auto n_rows = cluster.Get().size();
  QVERIFY(boost::num_vertices(concept_map) == n_rows + 1);
}

void ribi::braw::qtbrainweaverconceptmapdialog_test::a_file_with_cluster_only_will_create_a_concept_map()
{
  //using namespace cmap;
  const std::string question = "TESTQUESTION";
  File file;
  file.SetQuestion(question);
  Cluster cluster(
    {
      ribi::cmap::Concept("name 1"),
      ribi::cmap::Concept("name 2")
    }
  );
  file.SetCluster(cluster);

  QVERIFY(!boost::num_vertices(file.GetConceptMap()));

  const QtConceptMapDialog d(file);


  QVERIFY(boost::num_vertices(d.GetWidget()->GetConceptMap())
    == cluster.Get().size() + 1); //+1 because of focus question
}

void ribi::braw::qtbrainweaverconceptmapdialog_test::dialog_will_prefer_to_read_a_concept_map_over_a_cluster()
{
  File file;
  const auto cluster = ClusterFactory().GetTest( { 0,1,2 } );
  file.SetCluster(cluster);
  const ribi::cmap::ConceptMap concept_map(
    ribi::cmap::ConceptMapFactory().Get6()
  );
  const auto question = GetCenterNode(concept_map).GetConcept().GetName();
  file.SetQuestion(question);
  file.SetConceptMap(concept_map);
  const QtConceptMapDialog d(file);

  QVERIFY(d.GetWidget()->GetConceptMap() == concept_map);
}


void ribi::braw::qtbrainweaverconceptmapdialog_test::dialog_will_prefer_to_read_an_existing_concept_map_over_creating_one()
{
  using namespace cmap;
  File file;
  const ribi::cmap::ConceptMap concept_map(
    ConceptMapFactory().Get6()
  );
  const auto question = GetCenterNode(concept_map).GetConcept().GetName();
  file.SetQuestion(question);
  file.SetConceptMap(concept_map);
  const QtConceptMapDialog d(file);

  QVERIFY(d.GetWidget()->GetConceptMap() == concept_map);
}
