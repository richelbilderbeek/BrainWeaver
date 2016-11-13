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

ribi::braw::QtClusterDialog::QtClusterDialog(
  const File& file,
  QWidget* parent)
  : QtDialog(parent),
    ui(new Ui::QtClusterDialog),
    m_back_to_menu(false),
    m_file(file),
    m_widget(BuildWidget(file))
{
  ui->setupUi(this);

  //Remove help
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

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
      QLabel * const label = new QLabel(
        "Cannot start a new clustering "
        "when there is already a concept map created"
      );
      layout->addWidget(label);
    }
    ui->widget_tree->setLayout(layout);
  }
  //Enabled/disable controls
  const bool do_enable = CountCenterNodes(file.GetConceptMap()) == 0;
  if (m_widget) m_widget->setEnabled(do_enable);
  ui->edit->setEnabled(do_enable);

  //Add button
  {
    const bool had_concept_map = boost::num_vertices(file.GetConceptMap());
    ui->button_add->setEnabled(!had_concept_map);
  }

  //Display the focal question
  ui->label_question->setText(m_file.GetQuestion().c_str());
}


ribi::braw::QtClusterDialog::~QtClusterDialog() noexcept
{
  ///WARNING: assume ui->widget is not available anymore
  //const Cluster cluster = GetWidget()->GetCluster();
  //m_file.SetCluster(cluster);
  delete ui;
}

ribi::braw::QtClusterWidget * ribi::braw::BuildWidget(File file)
{
  // A concept map is already made, cluster has been left empty,
  // thus return null
  if (CountCenterNodes(file.GetConceptMap()) != 0
    && file.GetCluster().Get().empty()
  )
  {
    return nullptr;
  }

  //Read an existing cluster
  QtClusterWidget * const widget = new QtClusterWidget(file.GetCluster());
  assert(widget);
  return widget;
}

const ribi::braw::QtClusterWidget * ribi::braw::QtClusterDialog::GetWidget() const
{
  return m_widget;
}

ribi::braw::QtClusterWidget * ribi::braw::QtClusterDialog::GetWidget()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<QtClusterWidget*>(
    const_cast<const QtClusterDialog*>(this)->GetWidget());
}

void ribi::braw::QtClusterDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape)
  {
    emit remove_me(this);
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
  QDialog::keyPressEvent(e);

  #ifndef NDEBUG
  {
    //Check that writing to File works
    File file(m_file);
    const Cluster cluster = GetWidget()->GetCluster();
    file.SetCluster(cluster);
    assert(file.GetCluster() == GetWidget()->GetCluster());
  }
  #endif
}

void ribi::braw::QtClusterDialog::on_button_add_clicked()
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
    //Check that writing to File works
    File file(m_file);
    const Cluster cluster = GetWidget()->GetCluster();
    file.SetCluster(cluster);
    assert(file.GetCluster() == GetWidget()->GetCluster());
  }
  #endif
}

void ribi::braw::QtClusterDialog::on_button_next_clicked()
{
  if (GetWidget() && GetWidget()->isEnabled()) //Save concept map, when user is all
  {
    const Cluster cluster = GetWidget()->GetCluster();
    m_file.SetCluster(cluster);

    //File's cluster and widget's cluster should be the same
    assert(m_file.GetCluster() == GetWidget()->GetCluster());
  }

  QtConceptMapDialog * const d = new QtConceptMapDialog(m_file);
  emit add_me(d);

  //Will fail due to #85 at https://github.com/richelbilderbeek/Brainweaver/issues/85
  //The former architecture showed d modally, thus at this point d would have
  //a new file now. In this case, the file is read before modification

  //By now, the concept map must have been (1) created (2) already present
  if (d->GoBackToMenu())
  {
    m_back_to_menu = true;
    emit remove_me(this);
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

void ribi::braw::QtClusterDialog::Save()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de clustering op");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  assert(d->selectedFiles().size() == 1);
  const std::string filename = d->selectedFiles()[0].toStdString();
  Save(filename);
  //this->m_back_to_menu = true; //2013-04-19 Request by client
  //emit remove_me(this); //2013-04-19 Request by client
}

void ribi::braw::QtClusterDialog::Save(const std::string& filename)
{
  if (this->GetWidget())
  {
    assert(this->GetWidget());
    const Cluster cluster = this->GetWidget()->GetCluster();
    m_file.SetCluster(cluster);
    assert(m_file.GetCluster() == GetWidget()->GetCluster());
  }
  m_file.Save(filename);
}

void ribi::braw::QtClusterDialog::on_button_save_clicked()
{
  Save();
}
