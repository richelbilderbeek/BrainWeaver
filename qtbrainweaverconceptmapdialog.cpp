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
#include "qtbrainweaverconceptmapdialog.h"

#include <cassert>
#include <boost/lambda/lambda.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QLayout>
#include <QLabel>
#include <QMessageBox>

#include "add_custom_and_selectable_vertex.h"
#include "brainweavercluster.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapedge.h"
#include "brainweaverfile.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmap.h"
#include "qtconceptmap.h"
#include "qtconceptmapqtedge.h"
#include "qtbrainweaverfiledialog.h"
#include "qtconceptmapqtnode.h"
#include "qtbrainweaverprintconceptmapdialog.h"
#include "qtscopeddisable.h"
#include "trace.h"
#include "ui_qtbrainweaverconceptmapdialog.h"
#pragma GCC diagnostic pop

///Collect all QGraphicsItems with class T in an unorderly way
template <class T>
std::vector<T*> Collect(const QGraphicsScene* const scene)
{
  std::vector<T*> v;
  const QList<QGraphicsItem *> items = scene->items();
  std::transform(items.begin(),items.end(),std::back_inserter(v),
    [](QGraphicsItem* const item)
    {
      assert(item);
      return dynamic_cast<T*>(item);
    }
  );
  v.erase(std::remove(v.begin(),v.end(),nullptr),v.end());
  assert(std::count(v.begin(),v.end(),nullptr)==0);
  return v;
}

ribi::pvdb::QtPvdbConceptMapDialog::QtPvdbConceptMapDialog(
  const File& file,
  QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbConceptMapDialog),
    m_back_to_menu(false),
    m_file(file),
    m_widget(CreateWidget(file))
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  assert(boost::num_vertices(m_file.GetConceptMap()) > 0);
  assert(m_widget);
  assert(m_widget->GetConceptMap() == m_file.GetConceptMap());
  assert(this->layout());
  #endif

  
  this->layout()->addWidget(m_widget);

  //assert(!Collect<cmap::QtNode>(m_widget->scene()).empty()); //TODO RJCB: Put back in

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }

  #ifdef NOT_NOW_20141111
  m_widget->m_signal_conceptmapitem_requests_edit.connect(
    boost::bind(
      &ribi::pvdb::QtPvdbConceptMapDialog::OnConceptMapItemRequestsEdit,
      this,boost::lambda::_1));
  #endif
}

ribi::pvdb::QtPvdbConceptMapDialog::~QtPvdbConceptMapDialog() noexcept
{
  delete ui;
}

ribi::cmap::ConceptMap ribi::pvdb::QtPvdbConceptMapDialog::CreateFromCluster(
  const std::string& question,
  const Cluster& cluster)
{
  ribi::cmap::ConceptMap p;

  //Add center node
  add_custom_and_selectable_vertex(
    ribi::cmap::Node{
      ribi::cmap::Concept(question),
      true, //Center node
      0.0,
      0.0
    },
    false,
    p
  );


  const std::vector<ribi::cmap::Concept> v = cluster.Get();
  const int n = boost::numeric_cast<int>(v.size());
  const double delta_angle{2.0 * boost::math::constants::pi<double>() / static_cast<double>(n)};
  for (int i=0; i!=n; ++i)
  {
    const double angle{static_cast<double>(i) * delta_angle};
    const int x = -std::cos(angle) * 200.0;
    const int y =  std::sin(angle) * 200.0;
    ribi::cmap::Node node(v[i],false,x,y);
    add_custom_and_selectable_vertex(
      node,false,p
    );
  }
  assert(v.size() + 1 == boost::num_vertices(p)
    && "Assume the ConceptMap has as much nodes as the cluster has concepts + one focal question");
  return p;
}

ribi::cmap::QtConceptMap * ribi::pvdb::QtPvdbConceptMapDialog::CreateWidget(pvdb::File file)
{
  const bool trace_verbose = false;

  const bool had_cluster = !file.GetCluster().Empty();
  const bool had_concept_map = boost::num_vertices(file.GetConceptMap()) > 0;

  if (!had_cluster && !had_concept_map)
  {
    if (trace_verbose) { TRACE("User starts building a concept map from scratch"); }
    ribi::cmap::ConceptMap concept_map;
    add_custom_and_selectable_vertex(
      ribi::cmap::Node{
        ribi::cmap::Concept(file.GetQuestion()),
        true, //Center node
        0.0,
        0.0
      },
      false,
      concept_map
    );
    file.SetConceptMap(concept_map);
  }
  else if ( had_cluster && !had_concept_map)
  {
    if (trace_verbose) { TRACE("User supplied a filled-in cluster"); }
    ribi::cmap::ConceptMap concept_map {
      QtPvdbConceptMapDialog::CreateFromCluster(
        file.GetQuestion(),
        file.GetCluster()
      )
    };

    file.SetConceptMap(concept_map);

    assert((file.GetCluster().Get().size() + 1)
      == (boost::num_vertices(concept_map))
      && "As much cluster items as nodes + focus question");
  }

  if (!had_cluster && !had_concept_map)
  {
    assert(file.GetCluster().Empty());
    assert(boost::num_vertices(file.GetConceptMap()) > 0); //Created
  }
  if ( had_cluster && !had_concept_map)
  {
    assert(!file.GetCluster().Empty());
    assert(boost::num_vertices(file.GetConceptMap()) > 0); //Created from concept map
  }
  if (!had_cluster &&  had_concept_map)
  {
    assert(file.GetCluster().Empty());
    assert(boost::num_vertices(file.GetConceptMap()) > 0);
  }
  if ( had_cluster &&  had_concept_map)
  {
    assert(!file.GetCluster().Empty());
    assert(boost::num_vertices(file.GetConceptMap()) > 0);
  }

  ribi::cmap::QtConceptMap * const cmap{new ribi::cmap::QtConceptMap};
  assert(cmap);
  cmap->SetConceptMap(file.GetConceptMap());
  return cmap;
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbConceptMapDialog::DoRandomStuff()
{
  #ifdef NOT_NOW_20141224
  //Do random stuff
  assert(m_file);
  assert(m_file.GetConceptMap());
  assert(!m_GetNodes(file.GetConceptMap()).empty());
  assert(m_file.GetConceptMap().FindCenterNode()
    && "A file's ConceptMap must have a CenterNode");

  const int n_edges_before = boost::numeric_cast<int>(m_GetEdges(file.GetConceptMap()).size());
  const int n_nodes_before = boost::numeric_cast<int>(m_GetNodes(file.GetConceptMap()).size());
  this->GetWidget()->DoRandomStuff();
  const int n_edges_after = boost::numeric_cast<int>(m_GetEdges(file.GetConceptMap()).size());
  const int n_nodes_after = boost::numeric_cast<int>(m_GetNodes(file.GetConceptMap()).size());
  assert(n_edges_after > n_edges_before);
  assert(n_nodes_after > n_nodes_before);
  #endif // NOT_NOW_20141224
}
#endif

const ribi::cmap::QtConceptMap * ribi::pvdb::QtPvdbConceptMapDialog::GetWidget() const
{
  assert(m_widget);
  return m_widget;
}

ribi::cmap::QtConceptMap * ribi::pvdb::QtPvdbConceptMapDialog::GetWidget()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<cmap::QtConceptMap*>(
    const_cast<const QtPvdbConceptMapDialog*>(this)->GetWidget()); //?Why Dialog

}

void ribi::pvdb::QtPvdbConceptMapDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { on_button_save_clicked(); return; }
  if ((e->modifiers() & Qt::ControlModifier)
    && !(e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    QMessageBox box;
    box.setText("TODO: Undo");
    box.exec();
    return;
  }
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_Z)
  {
    QMessageBox box;
    box.setText("TODO: Redo");
    box.exec();
    return;
  }
  if ( (e->modifiers() & Qt::ControlModifier)
    && (e->modifiers() & Qt::ShiftModifier)
    && e->key() == Qt::Key_T)
  {
    //Translate
    this->setWindowTitle("Construction screen");
    ui->button_print->setText("Save as PDF-format");
    ui->button_save->setText("Save concept map");
    return;
  }

  QDialog::keyPressEvent(e);
}

void ribi::pvdb::QtPvdbConceptMapDialog::on_button_print_clicked()
{
  Save();
  QtPvdbPrintConceptMapDialog d(m_file);
  this->ShowChild(&d);
}

#ifdef NOT_NOW_20141111
void ribi::pvdb::QtPvdbConceptMapDialog::OnConceptMapItemRequestsEdit(cmap::QtConceptMapElement* const item)
{
  assert(item);
  {
    assert(this);
    assert(item);
    assert(item->GetNode());
    cmap::QtConceptMapConceptEditDialog d(item->GetNode().GetConcept());
    this->ShowChild(&d);
  }
  //item->GetConcept()->m_signal_examples_changed(item->GetConcept().get()); //NEW 2013-01-08 21:40
  item->m_signal_item_has_updated(item);
  item->update();
}
#endif // NOT_NOW_20141111

void ribi::pvdb::QtPvdbConceptMapDialog::on_button_save_clicked()
{
  //Temporarily disable to widget, otherwise saving cannot succeed
  const QtScopedDisable<cmap::QtConceptMap> scoped_disable1(GetWidget());
  const QtScopedDisable<QtPvdbConceptMapDialog> scoped_disable2(this);
  this->hide();

  const auto d = pvdb::QtFileDialog::GetSaveFileDialog(pvdb::QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de concept map op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename_raw = d->selectedFiles()[0].toStdString();
  const std::string filename
    =  (filename_raw.size() < pvdb::File::GetFilenameExtension().size()
      || filename_raw.substr( filename_raw.size() - 3, 3 ) != pvdb::File::GetFilenameExtension()
     ? filename_raw + "." + pvdb::File::GetFilenameExtension()
     : filename_raw);
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  Save(filename);
  //this->m_back_to_menu = true; //2013-04-19 Request by client
  //close(); //2013-04-19 Request by client
}

void ribi::pvdb::QtPvdbConceptMapDialog::Save() const
{
  //const ribi::cmap::ConceptMap concept_map = GetWidget()->GetConceptMap();
  //assert(boost::num_vertices(concept_map) > 0);
  assert(m_file.GetConceptMap() == GetWidget()->GetConceptMap());
  //m_file.SetConceptMap(concept_map);
}

void ribi::pvdb::QtPvdbConceptMapDialog::Save(const std::string& filename) const
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  Save();
  m_file.Save(filename);
}
