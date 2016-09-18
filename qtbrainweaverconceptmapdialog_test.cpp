#include "qtbrainweaverconceptmapdialog_test.h"

#include "add_custom_and_selectable_vertex.h"
#include "brainweaverclusterfactory.h"
#include "brainweavercluster.h"
#include "brainweaverfilefactory.h"
#include "brainweaverfile.h"
#include "conceptmapcenternodefactory.h"
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
#include "is_custom_vertices_isomorphic.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmapexamplesitem.h"
#include "qtconceptmap.h"
#include "qtconceptmaphelper.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtquadbezierarrowitem.h"

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
  ribi::braw::File file;
  const ribi::cmap::ConceptMap concept_map(
    ConceptMapFactory().Get6()
  );
  const auto question = ribi::cmap::GetCenterNode(concept_map).GetConcept().GetName();
  file.SetQuestion(question);
  file.SetConceptMap(concept_map);
  const QtConceptMapDialog d(file);

  QVERIFY(d.GetWidget()->GetConceptMap() == concept_map);
}

void ribi::braw::qtbrainweaverconceptmapdialog_test::create_edge_with_arrow_head()
{
  //Added this for https://github.com/richelbilderbeek/Brainweaver/issues/88
  //just to be sure that a QtConceptMap gets saved correctly
  using namespace cmap;
  File file = FileFactory().Get1();
  QtConceptMapDialog d(file);
  d.show();

  //Normally I'd say:
  //If you want to use 'd.GetQtConceptMap()' go work on the QtConceptMap tests
  QTest::keyClick(&d, Qt::Key_N, Qt::ControlModifier, 100);
  QTest::keyClick(&d, Qt::Key_N, Qt::ControlModifier, 100);
  QTest::keyClick(&d, Qt::Key_E, Qt::ControlModifier, 100);
  QTest::keyClick(&d, Qt::Key_H, Qt::ControlModifier, 100);

  const auto qtconceptmap = d.GetWidget();
  const auto qtnodes = ribi::cmap::GetQtNodes(qtconceptmap->GetScene());
  const auto excepted_vertices = 2;
  const auto measured_vertices = qtnodes.size();
  QVERIFY(measured_vertices == excepted_vertices);
  const auto qtedges = ribi::cmap::GetQtEdges(qtconceptmap->GetScene());
  const auto excepted_edges = 1;
  const auto measured_edges = qtedges.size();
  QVERIFY(measured_edges == excepted_edges);
  const QtEdge * const qtedge = qtedges[0];
  assert(qtedge);
  QVERIFY(qtedge->GetArrow()->HasHead());
  QVERIFY(qtedge->GetEdge().HasHeadArrow());
  QVERIFY(!qtedge->GetArrow()->HasTail());
  QVERIFY(!qtedge->GetEdge().HasTailArrow());

  const std::string filename{"create_edge_with_arrow_head.cmp"};
  d.UpdateFileWithConceptMapFromWidget();
  d.Save(filename);

  const std::string s = ToDot(LoadFile(filename).GetConceptMap());
  QVERIFY(s.find("<has_head>1</has_head>") != std::string::npos);
  QVERIFY(s.find("<has_tail>0</has_tail>") != std::string::npos);
  const std::string t = ToXml(LoadFile(filename).GetConceptMap());
  QVERIFY(t.find("<has_head>1</has_head>") != std::string::npos);
  QVERIFY(t.find("<has_tail>0</has_tail>") != std::string::npos);
}

void ribi::braw::qtbrainweaverconceptmapdialog_test
  ::node_with_vignette_must_show_examples()
{
  using namespace cmap;
  File file = FileFactory().Get4();
  QtConceptMapDialog d(file);
  d.show();

  for (int i=0; i!=100; ++i)
  {
    QTest::keyClick(&d, Qt::Key_Space, Qt::NoModifier, 100);
    //Must select one QtNode
    const auto qtnodes = ribi::cmap::GetSelectedQtNodes(d.GetWidget()->GetScene());
    if (qtnodes.size() != 1) continue;
    //QtNode must have an example
    const ribi::cmap::QtNode * const qtnode = qtnodes[0];
    if (qtnode->GetNode().GetConcept().GetExamples().Get().empty()) continue;

    //QtExamplesItem must have that QtNode as its buddy
    QVERIFY(d.GetWidget()->GetQtExamplesItem().GetBuddyItem() == qtnode);
  }
}
