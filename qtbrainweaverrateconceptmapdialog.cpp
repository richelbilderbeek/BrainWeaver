#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtbrainweaverrateconceptmapdialog.h"

#include <cassert>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>

#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "brainweaverfilefactory.h"
#include "qtbrainweaverfiledialog.h"
#include "qtscopeddisable.h"
#include "brainweaverfile.h"
#include "qtconceptmap.h"
#include "testtimer.h"
#include "trace.h"
#include "qtbrainweaverratingdialog.h"

#include "qtconceptmaprateconceptdialog.h"
#include "ui_qtbrainweaverrateconceptmapdialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtRateConceptMapDialog::QtRateConceptMapDialog(
  const File& file,
  QWidget* parent)
  : QtDialog(parent),
  ui(new Ui::QtRateConceptMapDialog),
  m_file(file),
  m_concept_map(new cmap::QtConceptMap)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  m_concept_map->SetConceptMap(file.GetConceptMap());
  m_concept_map->SetMode(ribi::cmap::Mode::rate);

  {
    assert(!ui->widget->layout());
    QLayout * const layout = new QGridLayout;
    ui->widget->setLayout(layout);
    layout->addWidget(m_concept_map);
  }

  {
    const std::string s = "Naam student: " + m_file.GetStudentName();
    ui->label_name->setText(s.c_str());
  }

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::braw::QtRateConceptMapDialog::~QtRateConceptMapDialog() noexcept
{
  this->m_concept_map->StopTimer();
  delete ui;
}

void ribi::braw::QtRateConceptMapDialog::changeEvent(QEvent * event)
{
  if (event->type() == QEvent::EnabledChange)
  {
    if (isEnabled())
    {
      this->m_concept_map->StartTimer();
    }
    else
    {
      this->m_concept_map->StopTimer();
    }
  }
}

const ribi::braw::File& ribi::braw::QtRateConceptMapDialog::GetFile() const noexcept
{
  return m_file;
}

ribi::cmap::QtConceptMap * ribi::braw::QtRateConceptMapDialog::GetWidget()
{
  assert(m_concept_map);
  return m_concept_map;
}

void ribi::braw::QtRateConceptMapDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { emit remove_me(this); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { Save(); return; }
  QDialog::keyPressEvent(e);
}

void ribi::braw::QtRateConceptMapDialog::on_button_next_clicked()
{
  m_file.SetConceptMap(m_concept_map->GetConceptMap());
  assert(m_concept_map->GetConceptMap() == m_file.GetConceptMap());
  m_concept_map->StopTimer();
  QtRatingDialog * const d{
    new QtRatingDialog(m_file)
  };
  emit add_me(d);

  //Will fail due to #85 at https://github.com/richelbilderbeek/Brainweaver/issues/85
  //The former architecture showed d modally, thus at this point d would have
  //a new file now. In this case, the file is read before modification
  if (d->GetBackToMenu())
  {
    emit remove_me(this);
  }
}

void ribi::braw::QtRateConceptMapDialog::Save()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  this->setEnabled(false);
  const int status = d->exec();
  this->setEnabled(true);
  if (status == QDialog::Rejected || d->selectedFiles().empty())
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename = d->selectedFiles()[0].toStdString();
  assert(!filename.empty());
  Save(filename);
  //emit remove_me(this); //Do not close after saving
  this->show();
}


void ribi::braw::QtRateConceptMapDialog::Save(const std::string& filename)
{
  m_file.SetConceptMap(m_concept_map->GetConceptMap());
  assert(m_concept_map->GetConceptMap() == m_file.GetConceptMap());
  //const ribi::cmap::ConceptMap concept_map = GetWidget()->GetConceptMap();
  //assert(boost::num_vertices(concept_map) > 0);
  //m_file.SetConceptMap(concept_map);
  //assert(IsEqual(*m_file.GetConceptMap(),*GetWidget()->GetConceptMap()));
  m_file.Save(filename);
}

void ribi::braw::QtRateConceptMapDialog::on_button_save_clicked()
{
  Save();
}

void ribi::braw::QtRateConceptMapDialog::showEvent(QShowEvent *)
{
  this->m_concept_map->setFocus();
}
