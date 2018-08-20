#ifndef QTBRAINWEAVERCLUSTERWIDGET_H
#define QTBRAINWEAVERCLUSTERWIDGET_H


#include <QTreeWidget>
#include "conceptmapcompetency.h"
#include "brainweavercluster.h"
#include "brainweaverfwd.h"

namespace ribi {
namespace braw {

class QtClusterTreeWidgetItem;
class QtClusterWidgetTest;


class QtClusterWidget : public QTreeWidget
{
  Q_OBJECT //!OCLINT

public:
  explicit QtClusterWidget(
    const Cluster& cluster,
    QWidget* parent = nullptr
  );

  void addTopLevelItem(QTreeWidgetItem *item);

  ///Add a top-level item
  void Add(const std::string& text);

  ///Get the cluster (after reading from the dialog)
  Cluster GetCluster() const noexcept;

protected:
  void dropEvent(QDropEvent *event);

  void keyPressEvent(QKeyEvent *event);

private slots:
  void RemoveEmptyItem(QTreeWidgetItem*,int);

private:
  ///The cluster
  ///Mutable because WriteToCluster updates it when GetCluster is called
  mutable Cluster m_cluster;

  ///Build the widget from the cluster
  void BuildCluster();

  ///Crash if the invariants are violated
  void CheckInvariants();

  ///Check that there are no items at depth three,
  ///which should always be the case
  bool HasNoItemsAtLevelThree() noexcept;

  ///The flags for an item at the bottom level, which is level 2
  Qt::ItemFlags GetBottomLevelFlags() const noexcept;

  ///Find out the depth of an item
  int GetDepth(const QTreeWidgetItem * const item) const;

  ///The flags for an item at the top level, which is level 1
  Qt::ItemFlags GetTopLevelFlags() const noexcept;

  ///Adds Concepts to concepts for a toplevelitem
  void ProcessTopLevelItem(
    QTreeWidgetItem * const top,
    std::vector<ribi::cmap::Concept>& concepts
  ) const;

  ///Write the widget its data to the cluster
  void WriteToCluster() const noexcept;

  void SetCorrectFlags() noexcept;

  void keyPressEventRight(QKeyEvent *event);

  friend class QtClusterWidgetTest;
};

///Move the ith child to top
void MoveJthChildToTop(
  QtClusterWidget * const widget,
  QTreeWidgetItem * const top,
  const int j
);

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCLUSTERWIDGET_H
