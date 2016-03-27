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
#include "qtbrainweaverclusterwidget.h"
#include <boost/test/unit_test.hpp>
#include <vector>

#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexample.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmapexamples.h"
#include "brainweaverclusterfactory.h"
#include "brainweavercluster.h"
#include "qtconceptmapcompetency.h"
#include "testtimer.h"
#include "qtbrainweaverclustertreewidgetitem.h"
#include "trace.h"

BOOST_AUTO_TEST_CASE(ribi_pvdb_qtclusterwidget_test)
{
  using namespace ribi::cmap;
  using namespace ribi::pvdb;
  {
    for (const Cluster& c: ClusterFactory().GetTests())
    {
      QtPvdbClusterWidget w(c);
      BOOST_CHECK(w.topLevelItemCount() == static_cast<int>(c.Get().size()));
      const Cluster d = w.GetCluster();
      BOOST_CHECK(c == d);
      QtPvdbClusterTreeWidgetItem * const item = new QtPvdbClusterTreeWidgetItem(
        Competency::misc,true,0,1,2);
      item->setText(0,QString("An extra line"));
      w.addTopLevelItem(item);
      BOOST_CHECK(w.topLevelItemCount() == static_cast<int>(c.Get().size()) + 1);
      const Cluster e = w.GetCluster();
      BOOST_CHECK(c != d);
      BOOST_CHECK(c == e);
      BOOST_CHECK(d != e);
    }
  }
}
