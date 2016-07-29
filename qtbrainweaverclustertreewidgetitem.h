#ifndef QTBRAINWEAVERCLUSTERTREEWIDGETITEM_H
#define QTBRAINWEAVERCLUSTERTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include "conceptmapcompetency.h"

namespace ribi {
namespace braw {

///QTreeWidgetItem with the only function of storing a cmap::Competency additionally
struct QtClusterTreeWidgetItem : public QTreeWidgetItem
{
  QTreeWidgetItem *clone() const;
  QtClusterTreeWidgetItem(
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

bool operator==(const QtClusterTreeWidgetItem& lhs, const QtClusterTreeWidgetItem& rhs) noexcept;

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERTREEWIDGETITEM_H
