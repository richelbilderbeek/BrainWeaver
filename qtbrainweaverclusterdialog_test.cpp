#include "qtbrainweaverclusterdialog_test.h"

#include <fstream>
#include <iostream>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/shared_ptr.hpp>

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>

#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "conceptmapcenternodefactory.h"

#include "conceptmapcompetency.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "brainweaverclusterfactory.h"
#include "brainweavercluster.h"
#include "brainweaverfilefactory.h"
#include "brainweaverfile.h"
#include "fileio.h"
#include "qtbrainweaverclusterwidget.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "ui_qtbrainweaverclusterdialog.h"

void ribi::braw::qtbrainweaverclusterdialog_test
  ::button_add_clicked_nothing_to_add()
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  d.on_button_add_clicked();
}

void ribi::braw::qtbrainweaverclusterdialog_test
  ::button_add_clicked_something_to_add()
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  d.ui->edit->setText("Something");
  d.on_button_add_clicked();
}

void ribi::braw::qtbrainweaverclusterdialog_test
  ::button_next_clicked_no_concept_map()
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  d.on_button_next_clicked();

}

void ribi::braw::qtbrainweaverclusterdialog_test
  ::button_next_clicked_with_concept_map()
{
  File file = FileFactory().Get5();
  assert(boost::num_vertices(file.GetConceptMap()));
  QtClusterDialog d(file);
  d.show();
  d.on_button_next_clicked();
}


void ribi::braw::qtbrainweaverclusterdialog_test
  ::cluster_dialog_must_be_enabled_if_there_is_no_concept_map()
{
  using namespace ribi::cmap;
  File file = FileFactory().Get0();

  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);

  QVERIFY(!file.GetCluster().Empty());
  QVERIFY(boost::num_vertices(file.GetConceptMap()) == 0);

  const QtClusterDialog d(file);
  const auto w = d.GetWidget();
  QVERIFY(w && w->isEnabled());
}

void ribi::braw::qtbrainweaverclusterdialog_test::
  cluster_dialog_must_be_disabled_if_there_are_nodes_in_the_concept_map()
{
  using namespace ribi::cmap;
  const std::string question = "question with spaces";
  File file;
  file.SetQuestion(question);

  const Cluster cluster = ClusterFactory().GetTest( { 0,1,2 } );

  file.SetCluster(cluster);

  const int index_1 = 1;
  QVERIFY(index_1 < ConceptFactory().GetNumberOfTests());
  const int index_2 = 2;
  QVERIFY(index_2 < ConceptFactory().GetNumberOfTests());

  file.SetConceptMap(CreateConceptMap(question));
  QtClusterDialog d(file);
  d.show();
  QVERIFY(d.GetWidget());
  QVERIFY(!d.GetWidget()->isEnabled());
}

void ribi::braw::qtbrainweaverclusterdialog_test::default_construct()
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
}

void ribi::braw::qtbrainweaverclusterdialog_test
  ::enable_button_depending_on_file()
{
  const auto v = File::GetTests();
  std::for_each(v.begin(),v.end(),
    [](const File& file)
    {
      const bool had_cluster = !file.GetCluster().Empty();
      const bool had_concept_map = boost::num_vertices(file.GetConceptMap());
      QtClusterDialog d{file};

      if (!had_cluster && !had_concept_map)
      {
        QVERIFY(d.GetUi()->button_add->isEnabled());
      }
      if ( had_cluster && !had_concept_map)
      {
        QVERIFY(d.GetUi()->button_add->isEnabled());
      }
      if (!had_cluster &&  had_concept_map)
      {
        QVERIFY(!d.GetUi()->button_add->isEnabled());
      }
      if ( had_cluster &&  had_concept_map)
      {
        QVERIFY(!d.GetUi()->button_add->isEnabled());
      }
    }
  );
}

void ribi::braw::qtbrainweaverclusterdialog_test::get_widget()
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  QVERIFY(d.GetWidget());
}

void ribi::braw::qtbrainweaverclusterdialog_test::press_escape()
{
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  QTest::keyClick(&d, Qt::Key_Escape);
}

void ribi::braw::qtbrainweaverclusterdialog_test::press_something()
{
  //Pressing something that has to be passed to child
  File file = FileFactory().Get0();
  const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );
  file.SetCluster(cluster);
  QtClusterDialog d(file);
  d.show();
  QTest::keyClick(&d, Qt::Key_0);
}

void ribi::braw::qtbrainweaverclusterdialog_test::save()
{
  File file = FileFactory().Get5();
  QtClusterDialog d(file);
  d.show();
  const std::string filename{"qtbrainweaverclusterdialog_test_save.cmp"};
  if (ribi::is_regular_file(filename)) { ribi::delete_file(filename); }
  assert(!ribi::is_regular_file(filename));
  d.Save(filename);
  QVERIFY(ribi::is_regular_file(filename));
}

