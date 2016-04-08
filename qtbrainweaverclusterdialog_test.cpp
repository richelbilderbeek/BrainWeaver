#include "qtbrainweaverclusterdialog_test.h"

#include <fstream>
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
#include "qtbrainweaverclusterwidget.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "trace.h"
#include "ui_qtbrainweaverclusterdialog.h"

void ribi::pvdb::qtbrainweaverclusterdialog_test::all_tests()
{
  using namespace ribi::cmap;
  //Regular tests
  {
    const std::vector<File> v = File::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const File& file)
      {
        const bool had_cluster = !file.GetCluster().Empty();
        const bool had_concept_map = boost::num_vertices(file.GetConceptMap());
        QtPvdbClusterDialog d{file};

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
        //Test cluster copying, if there
        if (!file.GetCluster().Empty())
        {
          QVERIFY(file.GetCluster().Empty() == d.GetWidget()->GetCluster().Empty());
          const Cluster before = file.GetCluster();
          QVERIFY(file.GetCluster() == before);
          d.GetWidget()->Add("Modification!");
          QVERIFY(d.GetWidget()->GetCluster() != before); //Widget updates the cluster
        }
      }
    );
  }
  #ifdef NOT_NOW_20160130
  {
    const std::vector<File > v = pvdb::File::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const File & file)
      {
        const bool had_cluster = file.GetCluster().get(); //.get() needed for crosscompiler
        const bool had_concept_map = file.GetConceptMap().get(); //.get() needed for crosscompiler

        boost::shared_ptr<QtPvdbClusterDialog> d(new QtPvdbClusterDialog(file));

        if (!had_cluster && !had_concept_map)
        {
          QVERIFY(!file.GetCluster().Empty());
          QVERIFY(!boost::num_vertices(file.GetConceptMap()));
          QVERIFY(d->ui->button_add->isEnabled());
        }
        if ( had_cluster && !had_concept_map)
        {
          QVERIFY(!file.GetCluster().Empty());
          QVERIFY(!boost::num_vertices(file.GetConceptMap()));
          QVERIFY(d->ui->button_add->isEnabled());
        }
        if (!had_cluster &&  had_concept_map)
        {
          QVERIFY(file.GetCluster().Empty());
          QVERIFY( file.GetConceptMap());
          QVERIFY(!d->ui->button_add->isEnabled());
        }
        if ( had_cluster &&  had_concept_map)
        {
          QVERIFY( file.GetCluster());
          QVERIFY( file.GetConceptMap());
          QVERIFY(!d->ui->button_add->isEnabled());
        }
        if (file.GetCluster())
        {

          const Cluster before = pvdb::ClusterFactory().DeepCopy(file.GetCluster());
          QVERIFY(before);
          QVERIFY(before != file.GetCluster());
          QVERIFY(operator==(*file.GetCluster(),*before));
          d->ui->edit->setText("modification");
          if (d->ui->button_add->isEnabled())
          {
            d->on_button_add_clicked();
            QVERIFY(!operator==(*before,*d->GetWidget()->GetCluster()));
          }
        }
      }
    );
  }
  #endif //NOT_NOW_20160130
  //QtPvdbClusterDialog must be enabled if there is no concept map
  {
    const std::string question = "TESTQUESTION";
    File file;
    file.SetQuestion(question);
    QVERIFY(file.GetQuestion() == question);

    const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );

    file.SetCluster(cluster);

    QVERIFY(!file.GetCluster().Empty());
    QVERIFY(boost::num_vertices(file.GetConceptMap()) == 0);

    const QtPvdbClusterDialog d(file);
    QVERIFY(d.GetWidget()->isEnabled()
      && "QtClusterWidget is enabled only when there is no ConceptMap");
  }

  //QtPvdbClusterDialog must be disabled if there are more nodes in the concept map
  {
    const std::string question = "TESTQUESTION";
    File file;
    file.SetQuestion(question);

    const Cluster cluster = ClusterFactory().GetTest( { 0,1,2 } );

    file.SetCluster(cluster);

    const int index_1 = 1;
    QVERIFY(index_1 < ConceptFactory().GetNumberOfTests());
    const int index_2 = 2;
    QVERIFY(index_2 < ConceptFactory().GetNumberOfTests());
    file.SetConceptMap(ribi::cmap::ConceptMapFactory().Get6());
    const QtPvdbClusterDialog d(file);
    QVERIFY(d.GetWidget());
    QVERIFY(!d.GetWidget()->isEnabled()
      && "QtClusterWidget is disabled when there is a filled ConceptMap");
  }
}
