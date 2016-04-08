#include "qtbrainweaverclusterwidget_test.h"

#include <vector>
#include "qtbrainweaverclusterwidget.h"
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

void ribi::pvdb::qtbrainweaverclusterwidget_test::all_tests()
{
  using namespace ribi::cmap;
  {
    for (const Cluster& c: ClusterFactory().GetTests())
    {
      QtPvdbClusterWidget w(c);
      QVERIFY(w.topLevelItemCount() == static_cast<int>(c.Get().size()));
      const Cluster d = w.GetCluster();
      QVERIFY(c == d);
      QtPvdbClusterTreeWidgetItem * const item = new QtPvdbClusterTreeWidgetItem(
        Competency::misc,true,0,1,2);
      item->setText(0,QString("An extra line"));
      w.addTopLevelItem(item);
      QVERIFY(w.topLevelItemCount() == static_cast<int>(c.Get().size()) + 1);
      const Cluster e = w.GetCluster();
      QVERIFY(c != d);
      QVERIFY(c == e);
      QVERIFY(d != e);
    }
  }
}
