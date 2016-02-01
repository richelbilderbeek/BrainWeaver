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
#include "qtbrainweaverclusterdialog.h"

#include <fstream>

#include <boost/algorithm/string/trim_all.hpp>
#include <boost/shared_ptr.hpp>

#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>

#include "qtbrainweaverconceptmapdialog.h"
#include "conceptmapcenternodefactory.h"

#include "conceptmapcompetency.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexamplefactory.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "brainweaverclusterfactory.h"
#include "brainweavercluster.h"
#include "brainweaverfilefactory.h"
#include "brainweaverfile.h"
#include "qtbrainweaverclusterwidget.h"
#include "qtbrainweaverconceptmapdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "trace.h"
#include "ui_qtbrainweaverclusterdialog.h"
#pragma GCC diagnostic pop

ribi::pvdb::QtPvdbClusterDialog::QtPvdbClusterDialog(
  const File& file,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbClusterDialog),
    m_back_to_menu(false),
    m_file(file),
    m_widget(BuildWidget(file))
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  //Add the cluster widget
  {
    assert(!ui->widget_tree->layout());
    QGridLayout * const layout = new QGridLayout;
    if (m_widget)
    {
      layout->addWidget(m_widget);
    }
    else
    {
      QLabel * const label = new QLabel("Cannot start a new clustering when there is already a concept map created");
      layout->addWidget(label);
    }
    ui->widget_tree->setLayout(layout);
  }
  //Enabled/disable controls
  const bool do_enable = CountCenterNodes(file.GetConceptMap()) == 0;
  ui->button_add->setEnabled(do_enable);
  if (m_widget) m_widget->setEnabled(do_enable);
  ui->edit->setEnabled(do_enable);

  //Display the focal question
  ui->label_question->setText(m_file.GetQuestion().c_str());
}


ribi::pvdb::QtPvdbClusterDialog::~QtPvdbClusterDialog() noexcept
{
  ///WARNING: assume ui->widget is not available anymore
  //const Cluster cluster = GetWidget()->GetCluster();
  //m_file.SetCluster(cluster);
  delete ui;
}

ribi::pvdb::QtPvdbClusterWidget * ribi::pvdb::QtPvdbClusterDialog::BuildWidget(File file)
{
  //Create a cluster a new cluster
  if (file.GetCluster().Get().empty() && CountCenterNodes(file.GetConceptMap()) == 0)
  {
    const Cluster cluster = pvdb::ClusterFactory().Create( {} );
     file.SetCluster(cluster);
  }
  //Read an existing cluster
  if (file.GetCluster().Get().empty())
  {
    QtPvdbClusterWidget * const widget = new QtPvdbClusterWidget(file.GetCluster());
    assert(widget);
    return widget;
  }
  //Only where there is an existing concept map, and no existing cluster, will this return null
  assert(!file.GetCluster().Get().empty() && CountCenterNodes(file.GetConceptMap()) > 0);
  return nullptr;
}

void ribi::pvdb::QtPvdbClusterDialog::DoRandomStuff()
{
  //TODO?
}


const ribi::pvdb::QtPvdbClusterWidget * ribi::pvdb::QtPvdbClusterDialog::GetWidget() const
{
  return m_widget;
}

ribi::pvdb::QtPvdbClusterWidget * ribi::pvdb::QtPvdbClusterDialog::GetWidget()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<QtPvdbClusterWidget*>(
    const_cast<const QtPvdbClusterDialog*>(this)->GetWidget());
}

void ribi::pvdb::QtPvdbClusterDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape)
  {
    close();
    return;
  }
  if (!m_widget)
  {
    return;
  }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S)
  {
    Save();
    return;
  }
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
    this->setWindowTitle("Association screen");
    ui->label_text_top->setText("If you reflect on the focus statement:");
    ui->label_text_middle->setText("Which important aspects of knowledge and attitude, examples, experiences and ideals do cross your mind?");
    ui->label_text_bottom->setText("Make a list and group the items.");
    ui->button_add->setText("Insert");
    ui->button_next->setText("Construct concept map");
    ui->button_save->setText("Save list");
    return;
  }
  QDialog::keyPressEvent(e);

  #ifndef NDEBUG
  {
    //Check that writing to pvdb::File works
    File file(m_file);
    const Cluster cluster = GetWidget()->GetCluster();
    file.SetCluster(cluster);
    assert(file.GetCluster() == GetWidget()->GetCluster());
  }
  #endif
}

void ribi::pvdb::QtPvdbClusterDialog::on_button_add_clicked()
{
  assert(m_widget && "This button can only be clicked when there is a widget");

  assert(boost::algorithm::trim_all_copy(std::string(" \t x \t ")) == "x");
  const std::string text = boost::algorithm::trim_all_copy(ui->edit->text().toStdString());
  if (text.empty()) return;
  //QStringList v;
  //v.append(text.c_str());
  //m_widget->addTopLevelItem(new QTreeWidgetItem(v));
  m_widget->Add(text);
  ui->edit->clear();
  ui->edit->setFocus();
  #ifndef NDEBUG
  {
    //Check that writing to pvdb::File works
    File file(m_file);
    const Cluster cluster = GetWidget()->GetCluster();
    file.SetCluster(cluster);
    assert(file.GetCluster() == GetWidget()->GetCluster());
  }
  #endif
}

void ribi::pvdb::QtPvdbClusterDialog::on_button_next_clicked()
{
  if (GetWidget() && GetWidget()->isEnabled()) //Save concept map, when user is all
  {
    const Cluster cluster = GetWidget()->GetCluster();
    m_file.SetCluster(cluster);

    //File's cluster and widget's cluster should be the same
    assert(m_file.GetCluster() == GetWidget()->GetCluster());
  }

  QtPvdbConceptMapDialog d(m_file);
  this->ShowChild(&d);

  //By now, the concept map must have been (1) created (2) already present
  if (d.GoBackToMenu())
  {
    m_back_to_menu = true;
    close();
  }

  //Same test as in constructor
  if (boost::num_vertices(m_file.GetConceptMap())) //1, as node[0] is focal question
  {
    if (m_widget)
    {
      m_widget->setEnabled(false);
      assert(!this->GetWidget()->isEnabled());
    }
    ui->button_add->setEnabled(false);
    ui->edit->setEnabled(false);
  }
}

#ifndef NDEBUG
void ribi::pvdb::QtPvdbClusterDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Regular tests
  {
    const std::vector<File> v = pvdb::File::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const File& file)
      {
        const bool had_cluster = !file.GetCluster().Empty();
        const bool had_concept_map = boost::num_vertices(file.GetConceptMap());
        QtPvdbClusterDialog d{file};

        if (!had_cluster && !had_concept_map)
        {
          assert(d.ui->button_add->isEnabled());
        }
        if ( had_cluster && !had_concept_map)
        {
          assert(d.ui->button_add->isEnabled());
        }
        if (!had_cluster &&  had_concept_map)
        {
          assert(!d.ui->button_add->isEnabled());
        }
        if ( had_cluster &&  had_concept_map)
        {
          assert(!d.ui->button_add->isEnabled());
        }
        //Test cluster copying, if there
        if (!file.GetCluster().Empty())
        {
          assert(file.GetCluster().Empty() == d.GetWidget()->GetCluster().Empty());
          const Cluster before = file.GetCluster();
          assert(file.GetCluster() == before);
          d.GetWidget()->Add("Modification!");
          assert(d.GetWidget()->GetCluster() != before); //Widget updates the cluster
        }
      }
    );
  }
  #ifdef NOT_NOW_20160130
  {
    const std::vector<File > v = pvdb::File::GetTests();
    std::for_each(v.begin(),v.end(),
      [](const File & file)
      {
        const bool had_cluster = file.GetCluster().get(); //.get() needed for crosscompiler
        const bool had_concept_map = file.GetConceptMap().get(); //.get() needed for crosscompiler

        boost::shared_ptr<QtPvdbClusterDialog> d(new QtPvdbClusterDialog(file));

        if (!had_cluster && !had_concept_map)
        {
          assert(!file.GetCluster().Empty());
          assert(!boost::num_vertices(file.GetConceptMap()));
          assert(d->ui->button_add->isEnabled());
        }
        if ( had_cluster && !had_concept_map)
        {
          assert(!file.GetCluster().Empty());
          assert(!boost::num_vertices(file.GetConceptMap()));
          assert(d->ui->button_add->isEnabled());
        }
        if (!had_cluster &&  had_concept_map)
        {
          assert(file.GetCluster().Empty());
          assert( file.GetConceptMap());
          assert(!d->ui->button_add->isEnabled());
        }
        if ( had_cluster &&  had_concept_map)
        {
          assert( file.GetCluster());
          assert( file.GetConceptMap());
          assert(!d->ui->button_add->isEnabled());
        }
        if (file.GetCluster())
        {

          const Cluster before = pvdb::ClusterFactory().DeepCopy(file.GetCluster());
          assert(before);
          assert(before != file.GetCluster());
          assert(operator==(*file.GetCluster(),*before));
          d->ui->edit->setText("modification");
          if (d->ui->button_add->isEnabled())
          {
            d->on_button_add_clicked();
            assert(!operator==(*before,*d->GetWidget()->GetCluster()));
          }
        }
      }
    );
  }
  #endif //NOT_NOW_20160130
  //QtPvdbClusterDialog must be enabled if there is no concept map
  {
    const std::string question = "TESTQUESTION";
    File file;
    file.SetQuestion(question);
    assert(file.GetQuestion() == question);

    const Cluster cluster = pvdb::ClusterFactory().GetTest( {0,1,2} );

    file.SetCluster(cluster);

    assert(!file.GetCluster().Empty());
    assert(boost::num_vertices(file.GetConceptMap()) == 0);

    const QtPvdbClusterDialog d(file);
    assert(d.GetWidget()->isEnabled()
      && "QtClusterWidget is enabled only when there is no ConceptMap");
  }

  //QtPvdbClusterDialog must be disabled if there are more nodes in the concept map
  {
    using namespace cmap;
    const std::string question = "TESTQUESTION";
    File file;
    file.SetQuestion(question);

    const Cluster cluster = pvdb::ClusterFactory().GetTest( { 0,1,2 } );

    file.SetCluster(cluster);

    const int index_1 = 1;
    assert(index_1 < ConceptFactory().GetNumberOfTests());
    const int index_2 = 2;
    assert(index_2 < ConceptFactory().GetNumberOfTests());
    file.SetConceptMap(ribi::cmap::ConceptMapFactory().Get6());
    const QtPvdbClusterDialog d(file);
    assert(d.GetWidget());
    assert(!d.GetWidget()->isEnabled()
      && "QtClusterWidget is disabled when there is a filled ConceptMap");
  }
}
#endif

void ribi::pvdb::QtPvdbClusterDialog::on_edit_textChanged(const QString &arg1)
{
  assert(ui->edit->text() == arg1);
  ui->button_add->setEnabled(boost::num_vertices(m_file.GetConceptMap()) && arg1.size() > 0);
}

void ribi::pvdb::QtPvdbClusterDialog::Save()
{
  const auto d = pvdb::QtFileDialog::GetSaveFileDialog(pvdb::QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de clustering op");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
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

void ribi::pvdb::QtPvdbClusterDialog::Save(const std::string& filename)
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == pvdb::File::GetFilenameExtension()
    && "File must have correct file extension name");
  if (this->GetWidget())
  {
    assert(this->GetWidget());
    const Cluster cluster = this->GetWidget()->GetCluster();
    m_file.SetCluster(cluster);
    assert(m_file.GetCluster() == GetWidget()->GetCluster());
  }
  m_file.Save(filename);
}

void ribi::pvdb::QtPvdbClusterDialog::on_button_save_clicked()
{
  Save();
}
