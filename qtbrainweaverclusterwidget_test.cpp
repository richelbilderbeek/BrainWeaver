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

void ribi::braw::qtbrainweaverclusterwidget_test::item_abuse()
{
  //This works
  QtClusterTreeWidgetItem(ribi::cmap::Competency::misc, false, 0, 0, 0);

  //These should fail
  try
  {
    QtClusterTreeWidgetItem(ribi::cmap::Competency::misc, false, -1, 0, 0);
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument&)
  {
    QVERIFY("Well done");
  }
  try
  {
    QtClusterTreeWidgetItem(ribi::cmap::Competency::misc, false, 0, -1, 0);
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument&)
  {
    QVERIFY("Well done");
  }
  try
  {
    QtClusterTreeWidgetItem(ribi::cmap::Competency::misc, false, 0, 0, -1);
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument&)
  {
    QVERIFY("Well done");
  }
}

void ribi::braw::qtbrainweaverclusterwidget_test::use()
{
  for (const Cluster& c: ClusterFactory().GetTests())
  {
    QtClusterWidget w(c);
    QVERIFY(w.topLevelItemCount() == static_cast<int>(c.Get().size()));
    const Cluster d = w.GetCluster();
    QVERIFY(c == d);
    QtClusterTreeWidgetItem * const item = new QtClusterTreeWidgetItem(
      ribi::cmap::Competency::misc,true,0,1,2);
    item->setText(0,QString("An extra line"));
    w.addTopLevelItem(item);
    QVERIFY(w.topLevelItemCount() == static_cast<int>(c.Get().size()) + 1);
    const Cluster e = w.GetCluster();
    QVERIFY(d != e);
  }
}
