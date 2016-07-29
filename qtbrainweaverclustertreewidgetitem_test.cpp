#include "qtbrainweaverclustertreewidgetitem_test.h"
#include "qtbrainweaverclustertreewidgetitem.h"

void ribi::braw::qtbrainweaverclustertreewidgetitem_test::default_construction()
{
  const QtClusterTreeWidgetItem * const i{
    new QtClusterTreeWidgetItem(ribi::cmap::Competency::misc, false, 1, 1, 1)
  };
  const QTreeWidgetItem * const j{i->clone()};
  const QtClusterTreeWidgetItem * const k{
    dynamic_cast<const QtClusterTreeWidgetItem *>(j)
  };
  QVERIFY(k);
  QVERIFY(*i == *k);
}
