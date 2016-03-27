#ifndef QTBRAINWEAVERCLUSTERTREEWIDGETITEM_H
#define QTBRAINWEAVERCLUSTERTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include "conceptmapcompetency.h"

namespace ribi {
namespace pvdb {

///QTreeWidgetItem with the only function of storing a cmap::Competency additionally
struct QtPvdbClusterTreeWidgetItem : public QTreeWidgetItem
{
  QtPvdbClusterTreeWidgetItem(
    const ribi::cmap::Competency competency,
    const bool is_complex,
    const int rating_complexity,
    const int rating_concreteness,
    const int rating_specifity
  );
  const ribi::cmap::Competency m_competency;
  const bool m_is_complex;
  const int m_rating_complexity;
  const int m_rating_concreteness;
  const int m_rating_specifity;
};

} //~namespace pvdb
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERTREEWIDGETITEM_H
