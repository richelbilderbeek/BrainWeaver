#include "qtbrainweaverconceptmapdialog_test.h"

#include "add_bundled_vertex.h"
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
#include "qtconceptmap.h"
#include "qtconceptmaphelper.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtquadbezierarrowitem.h"

using namespace ribi::braw;

void ribi::braw::QtConceptMapDialogTest
  ::FileHasConceptMapWithOneCenterNode()
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
    add_bundled_vertex(
      ribi::cmap::Node(
        ribi::cmap::Concept(question),
        ribi::cmap::NodeType::center
      ),
      concept_map
    );
    QVERIFY(boost::num_vertices(concept_map) > 0);
    file.SetConceptMap(concept_map);
    QVERIFY(file.GetQuestion() == question);
    QVERIFY(boost::num_vertices(file.GetConceptMap()));
    QVERIFY(!GetNodes(file.GetConceptMap()).empty());
    QVERIFY(HasCenterNode(file.GetConceptMap()));
    const QtConceptMapDialog d(file);
    assert(d.GetQtConceptMap());
    QVERIFY(boost::num_vertices(d.GetQtConceptMap()->ToConceptMap()) == 1);
  }
  catch (std::exception& e)
  {
    qDebug() << e.what();
    QVERIFY(!"Should not get here");
  }
}

void ribi::braw::QtConceptMapDialogTest::CreateFromCluster()
{
  const std::string question = "Focal question";
  ribi::braw::Cluster cluster(
    {
      ribi::cmap::Concept("Association 1"),
      ribi::cmap::Concept("Association 2"),
      ribi::cmap::Concept("Association 3")
    }
  );
  const auto concept_map = ::ribi::braw::CreateFromCluster(question, cluster);
  const auto n_concepts = cluster.Get().size();

  // +1 because the question also becomes a vertex
  QVERIFY(boost::num_vertices(concept_map) == n_concepts + 1);
  QVERIFY(CountCenterNodes(concept_map) == 1);
}

void ribi::braw::QtConceptMapDialogTest
  ::FileWithOnlyClusterCreatesConceptMap()
{
  File file;
  //Set a focal question
  {
    const std::string question = "Focal question";
    file.SetQuestion(question);
  }
  //Set a cluster
  {
    const Cluster cluster(
      {
        ribi::cmap::Concept("Association 1"),
        ribi::cmap::Concept("Association 2")
      }
    );
    file.SetCluster(cluster);
    assert(file.GetCluster() == cluster);
    QVERIFY(boost::num_vertices(file.GetConceptMap()) == 0);
  }
  const QtConceptMapDialog d(file);
  const auto qtconcept_map = d.GetQtConceptMap();
  QVERIFY(ribi::cmap::CountQtCenterNodes(*qtconcept_map) == 1);
  //Association 1, Association 2 and focal question
  QVERIFY(ribi::cmap::CountQtNodes(*qtconcept_map) == 3);
}

void ribi::braw::QtConceptMapDialogTest::DialogPrefersReadingConceptMapOverReadingCluster()
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

  const auto created = d.GetQtConceptMap()->ToConceptMap();
  QVERIFY(HasSimilarData(GetSortedNodes(concept_map), GetSortedNodes(created), 0.001));
  //Cannot assume same Edges, as they may change direction
  //QVERIFY(HasSimilarData(GetSortedEdges(concept_map), GetSortedEdges(created), 0.001));
}


void ribi::braw::QtConceptMapDialogTest
  ::DialogPrefersExistingConceptMapOverCreatingOne()
{
  using namespace cmap;
  ribi::braw::File file;
  const ribi::cmap::ConceptMap concept_map(
    ConceptMapFactory().Get6()
  );
  const auto question = ribi::cmap::GetCenterNode(concept_map).GetConcept().GetName();
  file.SetQuestion(question);
  file.SetConceptMap(concept_map);
  QtConceptMapDialog d(file);
  d.show();
  const auto created = d.GetQtConceptMap()->ToConceptMap();
  QVERIFY(HasSimilarData(GetSortedNodes(concept_map), GetSortedNodes(created), 0.001));
  //Cannot assume same Edges, as they may change direction
  //QVERIFY(HasSimilarData(GetSortedEdges(concept_map), GetSortedEdges(created), 0.001));
}

void ribi::braw::QtConceptMapDialogTest::CreateEdgeWithArrowHead()
{
  //Added this for https://github.com/richelbilderbeek/BrainWeaver/issues/88
  //just to be sure that a QtConceptMap gets saved correctly
  using namespace cmap;
  File file = FileFactory().Get1();
  QtConceptMapDialog d(file);
  d.show();
  const auto initial_n_qtnodes = ribi::cmap::GetQtNodes(d.GetQtConceptMap()->GetScene()).size();

  //Normally I'd say:
  //If you want to use 'd.GetQtConceptMap()' go work on the QtConceptMap tests
  QTest::qWait(100);
  QTest::keyClick(&d, Qt::Key_N, Qt::ControlModifier, 100);
  d.show();
  QTest::keyClick(&d, Qt::Key_N, Qt::ControlModifier, 100);
  d.show();
  QTest::keyClick(&d, Qt::Key_E, Qt::ControlModifier, 100);
  d.show();
  //New arrow has a head by default
  //QTest::keyClick(&d, Qt::Key_H, Qt::ControlModifier, 100);
  //d.show();

  const auto qtconceptmap = d.GetQtConceptMap();
  const auto qtnodes = ribi::cmap::GetQtNodes(qtconceptmap->GetScene());
  const auto expected_vertices = initial_n_qtnodes + 2;
  const auto n_measured_vertices = qtnodes.size();
  QVERIFY(n_measured_vertices == expected_vertices);
  const auto qtedges = ribi::cmap::GetQtEdges(qtconceptmap->GetScene());
  const auto excepted_edges = 1;
  const auto n_measured_edges = qtedges.size();
  QVERIFY(n_measured_edges == excepted_edges);
  const QtEdge * const qtedge = qtedges[0];
  assert(qtedge);
  //Arrow is either at head or tail
  QVERIFY(qtedge->GetArrow()->HasHead() ^ qtedge->GetArrow()->HasTail());
  QVERIFY(qtedge->GetEdge().HasHeadArrow() ^ qtedge->GetEdge().HasTailArrow());

  const QString filename{"create_edge_with_arrow_head.cmp"};
  d.UpdateFileWithConceptMapFromWidget();
  d.Save(filename);

  const std::string s = ToDot(LoadFile(filename.toStdString()).GetConceptMap());
  QVERIFY(
      (s.find("<has_head>1</has_head>") != std::string::npos)
    ^ (s.find("<has_tail>1</has_tail>") != std::string::npos)
  );
  QVERIFY(
      (s.find("<has_head>0</has_head>") != std::string::npos)
    ^ (s.find("<has_tail>0</has_tail>") != std::string::npos)
  );
  const std::string t = ToXml(LoadFile(filename.toStdString()).GetConceptMap());
  QVERIFY(
      (t.find("<has_head>1</has_head>") != std::string::npos)
    ^ (t.find("<has_tail>1</has_tail>") != std::string::npos)
  );
  QVERIFY(
      (t.find("<has_head>0</has_head>") != std::string::npos)
    ^ (t.find("<has_tail>0</has_tail>") != std::string::npos)
  );
}

void ribi::braw::QtConceptMapDialogTest::PressAltF4()
{
  File file = FileFactory().Get4();
  QtConceptMapDialog d(file);
  d.show();
  QTest::keyPress(&d, Qt::Key_F4, Qt::AltModifier);
}

void ribi::braw::QtConceptMapDialogTest::PressEscape()
{
  File file = FileFactory().Get4();
  QtConceptMapDialog d(file);
  d.show();
  QTest::keyPress(&d, Qt::Key_Escape);
}

void ribi::braw::QtConceptMapDialogTest::PressNonsense()
{
  File file = FileFactory().Get4();
  QtConceptMapDialog d(file);
  d.show();
  QTest::keyPress(&d, Qt::Key_X);
}
