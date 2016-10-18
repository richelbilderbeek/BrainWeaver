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
#include <iostream>
#include <boost/lambda/lambda.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/math/constants/constants.hpp>

#include <QEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>
#include <QTimer>

#include "add_custom_and_selectable_edge_between_vertices.h"
#include "add_custom_and_selectable_vertex.h"
#include "brainweavercluster.h"
#include "brainweaverfile.h"
#include "conceptmapcenternodefactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedge.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaverprintconceptmapdialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmap.h"
#include "qtconceptmap.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtscopeddisable.h"
#include "trace.h"
#include "ui_qtbrainweaverconceptmapdialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtConceptMapDialog::QtConceptMapDialog(
  const File& file,
  QWidget *parent)
  : QtDialog(parent),
    ui(new Ui::QtConceptMapDialog),
    m_back_to_menu(false),
    m_file(file),
    m_widget{new ribi::cmap::QtConceptMap(this)}
{
  if (!m_file.GetCluster().Empty() && boost::num_vertices(m_file.GetConceptMap()) == 0)
  {
    m_file.SetConceptMap(
      CreateFromCluster(m_file.GetQuestion(), m_file.GetCluster())
    );
  }
  if (boost::num_vertices(m_file.GetConceptMap()) == 0)
  {
    //Add the first central node
    using ribi::cmap::CenterNodeFactory;
    using ribi::cmap::Concept;
    const auto cn = CenterNodeFactory().Create(Concept(m_file.GetQuestion()));
    add_custom_and_selectable_vertex(cn, false, m_file.GetConceptMap());
    assert(boost::num_vertices(m_file.GetConceptMap()) > 0);
  }
  assert(boost::num_vertices(m_file.GetConceptMap()) > 0);
  assert(m_widget);

  ui->setupUi(this);
  m_widget->SetConceptMap(m_file.GetConceptMap());
  m_widget->SetMode(ribi::cmap::Mode::edit);

  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  assert(m_widget->GetConceptMap() == m_file.GetConceptMap());
  assert(this->layout());
  this->layout()->addWidget(m_widget);

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }

  //Start autosave
  {
    QTimer * const timer{new QTimer(this)};
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(on_autosave()));
    timer->setInterval(10000);
    timer->start();
  }
}

ribi::braw::QtConceptMapDialog::~QtConceptMapDialog() noexcept
{
  this->m_widget->StopTimer();
  delete ui;
}

ribi::cmap::ConceptMap ribi::braw::CreateFromCluster(
  const std::string& question,
  const Cluster& cluster)
{
  ribi::cmap::ConceptMap p;

  //Add center node
  const auto vd_center = add_custom_and_selectable_vertex(
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
    const double angle{(static_cast<double>(i) * delta_angle) + 0.00001}; //Add noise
    const int x =  std::sin(angle) * 200.0;
    const int y = -std::cos(angle) * 200.0;
    ribi::cmap::Node node(v[i],false,x,y);
    const auto vd_here = add_custom_and_selectable_vertex(
      node, false, p
    );
    add_custom_and_selectable_edge_between_vertices(
      ribi::cmap::Edge(ribi::cmap::Node()),
      false,
      vd_center,
      vd_here,
      p
    );
  }
  assert(v.size() + 1 == boost::num_vertices(p)
    && "Assume the ConceptMap has as much nodes as the cluster has concepts + one focal question");
  return p;
}

const ribi::cmap::QtConceptMap * ribi::braw::QtConceptMapDialog::GetWidget() const
{
  assert(m_widget);
  return m_widget;
}

ribi::cmap::QtConceptMap * ribi::braw::QtConceptMapDialog::GetWidget()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<cmap::QtConceptMap*>(
    const_cast<const QtConceptMapDialog*>(this)->GetWidget()); //?Why Dialog

}

bool ribi::braw::QtConceptMapDialog::GoBackToMenu() const noexcept
{
  return m_back_to_menu;
}

void ribi::braw::QtConceptMapDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape)
  {
    emit remove_me(this);
    return;
  }
  if (e->key() == Qt::Key_F4 && (e->modifiers() & Qt::AltModifier))
  {
    emit remove_me(this);
    return;
  }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S)
  {
    on_button_save_clicked(); return;
  }
  m_widget->keyPressEvent(e);
  if (!e->isAccepted())
  {
    QDialog::keyPressEvent(e);
  }
}

void ribi::braw::QtConceptMapDialog::on_button_print_clicked()
{
  UpdateFileWithConceptMapFromWidget();
  this->m_widget->setEnabled(false); //Prevents #101
  m_widget->StopTimer();
  QtPrintConceptMapDialog * const d = new QtPrintConceptMapDialog(m_file);
  emit add_me(d);

  //this->m_widget->setEnabled(true);
}

void ribi::braw::QtConceptMapDialog::on_autosave()
{
  if (!isVisible()) return;
  try
  {
    UpdateFileWithConceptMapFromWidget();
    m_file.AutoSave();
    qDebug() << __func__ << ": successfull autosave";
  }
  catch (std::exception& e)
  {
    qCritical() << __func__ << ": exception thrown with description " << e.what();
  }
}

void ribi::braw::QtConceptMapDialog::on_button_save_clicked()
{
  //Temporarily disable to widget, otherwise saving cannot succeed
  //const QtScopedDisable<cmap::QtConceptMap> scoped_disable1(GetWidget());
  //const QtScopedDisable<QtConceptMapDialog> scoped_disable2(this);
  //this->hide();

  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
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
    =  (filename_raw.size() < GetFilenameExtension().size()
      || filename_raw.substr( filename_raw.size() - 3, 3 ) != GetFilenameExtension()
     ? filename_raw + "." + GetFilenameExtension()
     : filename_raw);
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == GetFilenameExtension()
    && "File must have correct file extension name");
  UpdateFileWithConceptMapFromWidget();
  Save(filename);
  //this->m_back_to_menu = true; //2013-04-19 Request by client
  //emit remove_me(this); //2013-04-19 Request by client
}

void ribi::braw::QtConceptMapDialog::showEvent(QShowEvent *)
{
  m_widget->setFocus();
}

void ribi::braw::QtConceptMapDialog::UpdateFileWithConceptMapFromWidget()
{
  CheckInvariants(*GetWidget());

  m_file.SetConceptMap(GetWidget()->GetConceptMap());
  assert(m_file.GetConceptMap() == GetWidget()->GetConceptMap());

  CheckInvariants(*GetWidget());
}

void ribi::braw::QtConceptMapDialog::Save(const std::string& filename) const
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == GetFilenameExtension()
    && "File must have correct file extension name");
  if (m_file.GetConceptMap() != GetWidget()->GetConceptMap())
  {
    std::clog << __func__ << ": warning: you should have called "
      << "'UpdateFileWithConceptMapFromWidget' before saving, doing so now\n"
    ;
    const_cast<QtConceptMapDialog*>(this)->UpdateFileWithConceptMapFromWidget();
  }
  m_file.Save(filename);
}
