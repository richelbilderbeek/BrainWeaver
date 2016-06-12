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

#include "qtconceptmaprateconceptdialognewname.h"
#include "ui_qtbrainweaverrateconceptmapdialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtRateConceptMapDialog::QtRateConceptMapDialog(
  const File& file,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
  ui(new Ui::QtRateConceptMapDialog),
  m_file(file),
  m_concept_map(new cmap::QtConceptMap)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  m_concept_map->SetConceptMap(file.GetConceptMap());
  m_concept_map->SetMode(ribi::cmap::QtConceptMap::Mode::rate);

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


  this->m_concept_map->setFocus();
}

ribi::braw::QtRateConceptMapDialog::~QtRateConceptMapDialog() noexcept
{
  delete ui;
}

ribi::cmap::QtConceptMap * ribi::braw::QtRateConceptMapDialog::GetWidget()
{
  assert(m_concept_map);
  return m_concept_map;
}

void ribi::braw::QtRateConceptMapDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { Save(); return; }
  QDialog::keyPressEvent(e);
}

void ribi::braw::QtRateConceptMapDialog::on_button_next_clicked()
{
  m_file.SetConceptMap(m_concept_map->GetConceptMap());
  assert(m_concept_map->GetConceptMap() == m_file.GetConceptMap());
  QtRatingDialog d(m_file);
  ShowChild(&d);
  if (d.GetBackToMenu())
  {
    close();
  }
}

void ribi::braw::QtRateConceptMapDialog::Save()
{
  this->hide(); //Obligatory, otherwise program will freeze

  const auto d = QtFileDialog::GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  const int status = d->exec();
  if (status == QDialog::Rejected || d->selectedFiles().empty())
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename_raw = d->selectedFiles()[0].toStdString();
  assert(!filename_raw.empty());

  const std::string filename
    =  (filename_raw.size() < File::GetFilenameExtension().size()
      || filename_raw.substr( filename_raw.size() - 3, 3 ) != File::GetFilenameExtension()
     ? filename_raw + "." + File::GetFilenameExtension()
     : filename_raw);
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == File::GetFilenameExtension()
    && "File must have correct file extension name");
  Save(filename);
  //close(); //Do not close after saving
  this->show();
}


void ribi::braw::QtRateConceptMapDialog::Save(const std::string& filename)
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == File::GetFilenameExtension()
    && "File must have correct file extension name");
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
