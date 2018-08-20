#include "qtbrainweaverclusterwidget_test.h"

#include <cassert>
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
#include "qtbrainweaverclustertreewidgetitem.h"

void ribi::braw::QtClusterWidgetTest::item_abuse()
{
  //This works
  {
    const QtClusterTreeWidgetItem i(ribi::cmap::Competency::misc, false, 0, 0, 0);
    assert(i.m_competency == ribi::cmap::Competency::misc); //Don't care
  }

  //These should fail
  try
  {
    const QtClusterTreeWidgetItem i(ribi::cmap::Competency::misc, false, -2, 0, 0);
    assert(i.m_competency == ribi::cmap::Competency::misc); //Should not get here
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument&)
  {
    QVERIFY("Well done");
  }
  try
  {
    const QtClusterTreeWidgetItem i(ribi::cmap::Competency::misc, false, 0, -2, 0);
    assert(i.m_competency == ribi::cmap::Competency::misc); //Should not get here
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument&)
  {
    QVERIFY("Well done");
  }
  try
  {
    const QtClusterTreeWidgetItem i(ribi::cmap::Competency::misc, false, 0, 0, -2);
    assert(i.m_competency == ribi::cmap::Competency::misc); //Should not get here
    QVERIFY(!"Should not get here");
  }
  catch (std::invalid_argument&)
  {
    QVERIFY("Well done");
  }
}

void ribi::braw::QtClusterWidgetTest::use()
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
