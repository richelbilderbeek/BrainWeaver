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
#include "qtbrainweaverratingdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>

#include <QDebug>
#include <QKeyEvent>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QPainter>
#include <QPrinter>

#include "conceptmap.h"
#include "qtconceptmap.h"
#include "qtbrainweaverprintratingdialog.h"
#include "qtconceptmap.h"
#include "qtbrainweaverdisplay.h"
#include "qtbrainweaverfiledialog.h"
#include "qtconceptmapdisplaystrategy.h"
#include "brainweaverfile.h"
#include "trace.h"
#include "ui_qtbrainweaverratingdialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtRatingDialog::QtRatingDialog(
  const File file,
  QWidget* parent)
  : QtDialog(parent),
    ui(new Ui::QtRatingDialog),
    m_back_to_menu(false),
    m_file(file)
{
  if (boost::num_vertices(file.GetConceptMap()) == 0)
  {
    std::stringstream msg;
    msg << __func__ << ": must have at least one node";
    throw std::invalid_argument(msg.str());
  }

  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  //Student name
  {
    const std::string s = "Naam student: " + file.GetStudentName();
    ui->label_student_name->setText(s.c_str());
  }
  //Assessor name
  {
    ui->label_assessor_name->setText("Naam assessor: ");
    if (!file.GetAssessorName().empty())
    {
      ui->edit_name->setText(file.GetAssessorName().c_str());
      //ui->edit_name->setReadOnly(true); //TVDB request
      ui->button_print->setEnabled(true);
    }
    else
    {
      ui->edit_name->setFocus(); //Needs to be done in showEvent
      ui->button_print->setEnabled(false);
    }
  }

  
  QtDisplay().DisplayRatedConcepts(file,ui->table_concepts);
  QtDisplay().DisplayExamples(file,ui->table_examples);
  QtDisplay().DisplayValues(file,ui->table_values);
  QtDisplay().DisplayMiscValues(file,ui->table_misc_values);

  //Center the dialog
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(screen.adjusted(64,64,-64,-64));
    this->move(screen.center() - this->rect().center());
  }

}

ribi::braw::QtRatingDialog::~QtRatingDialog() noexcept
{
  delete ui;
}

void ribi::braw::QtRatingDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape) { emit remove_me(this); }
}

void ribi::braw::QtRatingDialog::on_button_save_clicked()
{
  //Temporarily disable to widget, otherwise saving cannot succeed
  this->hide();

  const auto d = QtFileDialog::GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla het assessment invoer-bestand op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
    this->show();
    return;
  }
  assert(d->selectedFiles().size() == 1);
  const std::string filename_raw = d->selectedFiles()[0].toStdString();
  assert(!filename_raw.empty());

  const std::string filename
    =  (filename_raw.size() < GetFilenameExtension().size()
      || filename_raw.substr( filename_raw.size() - 3, 3 ) != GetFilenameExtension()
     ? filename_raw + "." + GetFilenameExtension()
     : filename_raw);
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == GetFilenameExtension()
    && "File must have correct file extension name");
  Save(filename);
  this->m_back_to_menu = true;
  emit remove_me(this);
}

void ribi::braw::QtRatingDialog::Save(const std::string& filename) const
{
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == GetFilenameExtension()
    && "File must have correct file extension name");

  m_file.Save(filename);
  //{ const std::string debug_str = "File saved as " + filename; TRACE(debug_str); }
}



void ribi::braw::QtRatingDialog::on_button_print_clicked()
{
  QtPrintRatingDialog * const d{
    new QtPrintRatingDialog(this->m_file)
  };

  //Center the dialog
  if (!"this will work")
  {
    const QRect screen = QApplication::desktop()->screenGeometry();
    d->setGeometry(screen.adjusted(64,64,-64,-64));
    d->move( screen.center() - d->rect().center() );
  }

  emit add_me(d);
}

void ribi::braw::QtRatingDialog::on_edit_name_textEdited(const QString &arg1)
{
  if (arg1.size() > 1)
  {
    m_file.SetAssessorName(arg1.toStdString());
    ui->button_print->setEnabled(true);
  }
  else
  {
    ui->button_print->setEnabled(false);
  }
}

void ribi::braw::QtRatingDialog::showEvent(QShowEvent *)
{
  ui->edit_name->setFocus();
}
