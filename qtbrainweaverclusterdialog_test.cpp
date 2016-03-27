//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectBrainweaver.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtbrainweaverclusterdialog.h"
#include <boost/test/unit_test.hpp>

#include <fstream>

#include <boost/algorithm/string/trim_all.hpp>
#include <boost/shared_ptr.hpp>

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>

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

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ribi_pvdb_qtclusterdialog_test)
{
  using namespace ribi::cmap;
  using namespace ribi::pvdb;
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
          BOOST_CHECK(d.GetUi()->button_add->isEnabled());
        }
        if ( had_cluster && !had_concept_map)
        {
          BOOST_CHECK(d.GetUi()->button_add->isEnabled());
        }
        if (!had_cluster &&  had_concept_map)
        {
          BOOST_CHECK(!d.GetUi()->button_add->isEnabled());
        }
        if ( had_cluster &&  had_concept_map)
        {
          BOOST_CHECK(!d.GetUi()->button_add->isEnabled());
        }
        //Test cluster copying, if there
        if (!file.GetCluster().Empty())
        {
          BOOST_CHECK(file.GetCluster().Empty() == d.GetWidget()->GetCluster().Empty());
          const Cluster before = file.GetCluster();
          BOOST_CHECK(file.GetCluster() == before);
          d.GetWidget()->Add("Modification!");
          BOOST_CHECK(d.GetWidget()->GetCluster() != before); //Widget updates the cluster
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
          BOOST_CHECK(!file.GetCluster().Empty());
          BOOST_CHECK(!boost::num_vertices(file.GetConceptMap()));
          BOOST_CHECK(d->ui->button_add->isEnabled());
        }
        if ( had_cluster && !had_concept_map)
        {
          BOOST_CHECK(!file.GetCluster().Empty());
          BOOST_CHECK(!boost::num_vertices(file.GetConceptMap()));
          BOOST_CHECK(d->ui->button_add->isEnabled());
        }
        if (!had_cluster &&  had_concept_map)
        {
          BOOST_CHECK(file.GetCluster().Empty());
          BOOST_CHECK( file.GetConceptMap());
          BOOST_CHECK(!d->ui->button_add->isEnabled());
        }
        if ( had_cluster &&  had_concept_map)
        {
          BOOST_CHECK( file.GetCluster());
          BOOST_CHECK( file.GetConceptMap());
          BOOST_CHECK(!d->ui->button_add->isEnabled());
        }
        if (file.GetCluster())
        {

          const Cluster before = pvdb::ClusterFactory().DeepCopy(file.GetCluster());
          BOOST_CHECK(before);
          BOOST_CHECK(before != file.GetCluster());
          BOOST_CHECK(operator==(*file.GetCluster(),*before));
          d->ui->edit->setText("modification");
          if (d->ui->button_add->isEnabled())
          {
            d->on_button_add_clicked();
            BOOST_CHECK(!operator==(*before,*d->GetWidget()->GetCluster()));
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
    BOOST_CHECK(file.GetQuestion() == question);

    const Cluster cluster = ClusterFactory().GetTest( {0,1,2} );

    file.SetCluster(cluster);

    BOOST_CHECK(!file.GetCluster().Empty());
    BOOST_CHECK(boost::num_vertices(file.GetConceptMap()) == 0);

    const QtPvdbClusterDialog d(file);
    BOOST_CHECK(d.GetWidget()->isEnabled()
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
    BOOST_CHECK(index_1 < ConceptFactory().GetNumberOfTests());
    const int index_2 = 2;
    BOOST_CHECK(index_2 < ConceptFactory().GetNumberOfTests());
    file.SetConceptMap(ribi::cmap::ConceptMapFactory().Get6());
    const QtPvdbClusterDialog d(file);
    BOOST_CHECK(d.GetWidget());
    BOOST_CHECK(!d.GetWidget()->isEnabled()
      && "QtClusterWidget is disabled when there is a filled ConceptMap");
  }
}
