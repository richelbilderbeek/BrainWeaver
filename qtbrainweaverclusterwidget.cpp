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

#include <cassert>
#include <sstream>
#include <vector>

#include <QDebug>
#include <QKeyEvent>

#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapexample.h"
#include "conceptmapexamplesfactory.h"
#include "conceptmapexamples.h"
#include "brainweaverclusterfactory.h"
#include "qtbrainweaverclustertreewidgetitem.h"
#include "brainweavercluster.h"
#include "qtconceptmapcompetency.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::braw::QtClusterWidget::QtClusterWidget(
  const Cluster& cluster,
  QWidget* parent)
  : QTreeWidget(parent),
    m_cluster{cluster}
{
  //Hide the header
  this->setHeaderHidden(true);

  //Let the row colors alternate
  this->setAlternatingRowColors(true);

  //Allow items to be drag and dropped inside of the widget
  this->setDragDropMode(QAbstractItemView::InternalMove);

  //Let the drag and drop be animated
  this->setAnimated(true);

  this->BuildCluster();

  QObject::connect(
    this,
    SIGNAL(itemChanged(QTreeWidgetItem*,int)),
    this,
    SLOT(RemoveEmptyItem(QTreeWidgetItem*,int)));

  // Allow word-wrapping
  this->setWordWrap(true);
}

void ribi::braw::QtClusterWidget::Add(const std::string& text)
{
  QtClusterTreeWidgetItem * const item = new QtClusterTreeWidgetItem(
    cmap::Competency::uninitialized,true,-1,-1,-1);
  item->setText(0,text.c_str());
  this->addTopLevelItem(item);
  SetCorrectFlags();
}

void ribi::braw::QtClusterWidget::addTopLevelItem(QTreeWidgetItem *item)
{
  if (!dynamic_cast<QtClusterTreeWidgetItem*>(item))
  {
    std::stringstream msg;
    msg << __func__ << ": "
      << "must add items of type 'QtClusterTreeWidgetItem'"
    ;
    throw std::invalid_argument(msg.str());
  }
  QTreeWidget::addTopLevelItem(item);
}


void ribi::braw::QtClusterWidget::dropEvent(QDropEvent *event)
{
  QTreeWidget::dropEvent(event);
  //Fix the possibility of dropping a tree with depth three
  while (1)
  {
    bool done = true;
    const int n_top = this->topLevelItemCount();
    for (int i=0; i!=n_top; ++i)
    {
      assert(i < this->topLevelItemCount());
      QTreeWidgetItem * const top = this->topLevelItem(i);
      assert(top);
      const int n_child = top->childCount();
      for (int j=0; j!=n_child; ++j)
      {
        assert(j < top->childCount());
        //Check if top->child(j) has children
        if (top->child(j)->childCount() > 0)
        {
          MoveJthChildToTop(top, j);
          done = false;
          j = n_child - 1;
          i = n_top - 1;
        }
      }
    }
    //End the while loop if no parents were moved
    if (done) break;
  }
  assert(HasNoItemsAtLevelThree());
  SetCorrectFlags();
}


bool ribi::braw::QtClusterWidget::HasNoItemsAtLevelThree() noexcept
{
  const int n_top = this->topLevelItemCount();
  for (int i=0; i!=n_top; ++i)
  {
    QTreeWidgetItem * const top = this->topLevelItem(i);
    assert(top);

    const int n_child = top->childCount();
    for (int j=0; j!=n_child; ++j)
    {
      if (top->child(j)->childCount() > 0)
      {
        return false;
      }
    }
  }
  return true;
}

void ribi::braw::QtClusterWidget::MoveJthChildToTop(
  QTreeWidgetItem * const top,
  const int j
) noexcept
{
  QTreeWidgetItem * const clone = top->child(j)->clone();
  assert(clone);
  this->addTopLevelItem(clone);
  top->removeChild(top->child(j));
}

//Process all items
void ribi::braw::QtClusterWidget::SetCorrectFlags() noexcept
{
  const int n_top = this->topLevelItemCount();
  for (int i=0; i!=n_top; ++i)
  {
    QTreeWidgetItem * const top = this->topLevelItem(i);
    assert(top);

    //Let all top items auto-expand
    top->setExpanded(true);

    //Allow dropping on top-level items
    top->setFlags(
          Qt::ItemIsSelectable
        | Qt::ItemIsEnabled
        | Qt::ItemIsEditable
        | Qt::ItemIsDragEnabled
        | Qt::ItemIsDropEnabled);
    assert(GetDepth(top)==0);
    const int n_child = top->childCount();
    for (int j=0; j!=n_child; ++j)
    {
        assert(GetDepth(top->child(j))==1);
        //Disallow dropping on non-top-level items
        top->child(j)->setFlags(
              Qt::ItemIsSelectable
          | Qt::ItemIsEnabled
          | Qt::ItemIsEditable
          | Qt::ItemIsDragEnabled);
    }
  }
}

ribi::braw::Cluster ribi::braw::QtClusterWidget::GetCluster() const noexcept
{
  WriteToCluster();
  return m_cluster;
}

int ribi::braw::QtClusterWidget::GetDepth(const QTreeWidgetItem * const item) const
{
  assert(item);
  int depth = 0;
  const QTreeWidgetItem * copy = item->parent();
  while(copy)
  {
    ++depth;
    copy = copy->parent();
  }
  return depth;
}

void ribi::braw::QtClusterWidget::keyPressEvent(QKeyEvent *event)
{
  //Without this seemingly useless member function,
  //the widget cannot be edited
  QTreeWidget::keyPressEvent(event);
  switch (event->key())
  {
    case Qt::Key_Space:
    case Qt::Key_Select:
      if(currentItem())
      {
        emit QTreeWidget::itemClicked(currentItem(), 0);
      }
    break;
    case Qt::Key_Right: keyPressEventRight(event); break;
//    case Qt::Key_Left:
//    {
//      auto cur_item = currentItem();
//      if (cur_item && GetDepth(cur_item) == 1)
//      {
//        assert(cur_item->parent());
//        const auto parent = cur_item->parent();
//        const auto clone = cur_item->clone();
//        auto above = itemAbove(cur_item);
//        parent->removeChild(cur_item);
//        above->addChild(clone);
//        delete cur_item;
//        clone->setSelected(true);
//        //assert(GetDepth(clone) == 1);
//      }
//    }
//    break;

    default: break;
  }
}

void ribi::braw::QtClusterWidget::keyPressEventRight(QKeyEvent *)
{
  auto cur_item = currentItem();
  assert(dynamic_cast<QtClusterTreeWidgetItem*>(cur_item));
  if (cur_item && GetDepth(cur_item) == 0)
  {
    assert(!cur_item->parent());

    //Move to higher level
    //const auto parent = cur_item->parent();
    const auto clone = cur_item->clone();
    assert(dynamic_cast<QtClusterTreeWidgetItem*>(clone));
    auto above = itemAbove(cur_item);
    if (above)
    {
      above->addChild(clone);
      above->setSelected(false);
    }
    else
    {
      this->addTopLevelItem(clone);
    }
    delete cur_item;
    clone->setSelected(true);
    //assert(GetDepth(clone) == 1);
  }
}

void ribi::braw::QtClusterWidget::BuildCluster()
{
  CheckInvariants();

  this->clear();
  const std::vector<ribi::cmap::Concept>& v = m_cluster.Get();
  std::for_each(v.begin(),v.end(),
    [this](const ribi::cmap::Concept& concept)
    {
      assert(concept.GetRatingComplexity() >= -1);
      assert(concept.GetRatingComplexity() <=  2);
      QtClusterTreeWidgetItem * const top
        = new QtClusterTreeWidgetItem(
          cmap::Competency::uninitialized,
          concept.GetIsComplex(),
          concept.GetRatingComplexity(),
          concept.GetRatingConcreteness(),
          concept.GetRatingSpecificity()
          );
      top->setText(0,concept.GetName().c_str());
      const auto examples = concept.GetExamples().Get();
      std::for_each(examples.begin(),examples.end(),
        [top,this](const ribi::cmap::Example& example)
        {
          QtClusterTreeWidgetItem * const child_item
            = new QtClusterTreeWidgetItem(
              example.GetCompetency(),
              example.GetIsComplex(),
              -1, //An example is not rated for complexity
              -1, //An example is not rated for concreteness
              -1  //An example is not rated for specifity
            );
          child_item->setText(0,example.GetText().c_str());
          top->addChild(child_item);
          child_item->setFlags(GetBottomLevelFlags());
        }
      );
      this->addTopLevelItem(top);
      top->setExpanded(true);
      top->setFlags(GetTopLevelFlags());
    }
  );
}

void ribi::braw::QtClusterWidget::CheckInvariants()
{
  assert(this->isHeaderHidden());
  assert(this->alternatingRowColors());
  assert(this->dragDropMode() == QAbstractItemView::InternalMove);
  assert(this->isAnimated());
}

Qt::ItemFlags ribi::braw::QtClusterWidget::GetBottomLevelFlags() const noexcept
{
  return Qt::ItemIsSelectable
    | Qt::ItemIsEnabled
    | Qt::ItemIsEditable
    | Qt::ItemIsDragEnabled
  ;
}

Qt::ItemFlags ribi::braw::QtClusterWidget::GetTopLevelFlags() const noexcept
{
  return Qt::ItemIsSelectable
    | Qt::ItemIsEnabled
    | Qt::ItemIsEditable
    | Qt::ItemIsDragEnabled
    | Qt::ItemIsDropEnabled
  ;
}

void ribi::braw::QtClusterWidget::RemoveEmptyItem(QTreeWidgetItem* item,int col)
{

  if (item->text(col).isEmpty())
  {
    delete item;
    this->update();
  }
}

void ribi::braw::QtClusterWidget::ProcessTopLevelItem(
  QTreeWidgetItem * const top,
  std::vector<ribi::cmap::Concept>& concepts
) const
{
  const std::string name = top->text(0).toStdString();
  std::vector<ribi::cmap::Example> examples;

  const int n_child = top->childCount();
  for (int j=0; j!=n_child; ++j)
  {
    const QtClusterTreeWidgetItem * const braw_item
      = dynamic_cast<QtClusterTreeWidgetItem *>(top->child(j));
    const cmap::Competency competency = braw_item
      ? braw_item->m_competency : cmap::Competency::uninitialized;
    assert(GetDepth(top->child(j))==1);
    ribi::cmap::Example p(
      top->child(j)->text(0).toStdString(),
      competency
    );
    examples.push_back(p);
  }

  QtClusterTreeWidgetItem * const braw_top
    = dynamic_cast<QtClusterTreeWidgetItem *>(top);
  using namespace cmap;

  if (braw_top)
  {
    concepts.push_back(
      ribi::cmap::Concept(
        name, Examples(examples),
        braw_top->m_is_complex,
        braw_top->m_rating_complexity,
        braw_top->m_rating_concreteness,
        braw_top->m_rating_specifity
      )
    );
  }
  else
  {
    concepts.push_back(
      ribi::cmap::Concept(name, Examples(examples), true, -1, -1, -1)
    );
  }
}

void ribi::braw::QtClusterWidget::WriteToCluster() const noexcept
{
  std::vector<ribi::cmap::Concept> concepts;
  const int n_top = this->topLevelItemCount();
  for (int i=0; i!=n_top; ++i)
  {
    QTreeWidgetItem * const top = this->topLevelItem(i);
    assert(top);
    ProcessTopLevelItem(top, concepts);
  }

  m_cluster.SetConcepts(concepts);
  assert(n_top == static_cast<int>(m_cluster.Get().size())
    && "As much top-level items in a QtClusterWidget as Concepts in a Cluster");
}
