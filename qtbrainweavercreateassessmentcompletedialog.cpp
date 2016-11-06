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
#include "qtbrainweavercreateassessmentcompletedialog.h"

#include <sstream>
#include <stdexcept>

#include <QKeyEvent>
#include <QFileDialog>

#include "conceptmap.h"
#include "brainweaverfile.h"
#include "conceptmapfactory.h"
#include "qtbrainweaverfiledialog.h"

#include "ui_qtbrainweavercreateassessmentcompletedialog.h"

#include "trace.h"
#pragma GCC diagnostic pop

ribi::braw::QtCreateAssessmentCompleteDialog::QtCreateAssessmentCompleteDialog(QWidget* parent)
  : QtDialog(parent),
    ui(new Ui::QtCreateAssessmentCompleteDialog),
    m_back_to_menu(false)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
}

ribi::braw::QtCreateAssessmentCompleteDialog::~QtCreateAssessmentCompleteDialog() noexcept
{
  delete ui;
}

std::string ribi::braw::QtCreateAssessmentCompleteDialog::GetQuestion() const noexcept
{
  return ui->edit->text().toStdString();
}

void ribi::braw::QtCreateAssessmentCompleteDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { emit remove_me(this); return; }
}

void ribi::braw::QtCreateAssessmentCompleteDialog::on_button_save_clicked()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
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
    && "File must have correct file extension");
  Save(filename);

  m_back_to_menu = true;
  emit remove_me(this);
}

void ribi::braw::QtCreateAssessmentCompleteDialog::Save(const std::string& filename) const
{
  const std::string question = ui->edit->text().toStdString();
  File file;
  file.SetQuestion(question);
  assert(file.GetQuestion() == question);
  file.Save(filename);
}

void ribi::braw::QtCreateAssessmentCompleteDialog::SetQuestion(const std::string& question)
{
  ui->edit->setText(question.c_str());
}

void ribi::braw::QtCreateAssessmentCompleteDialog::on_edit_textChanged(const QString &arg1)
{
  assert(ui->edit->text() == arg1);
  ui->button_save->setEnabled(!arg1.isEmpty());

}
