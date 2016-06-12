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
#include "qtbrainweaverstudentmenudialog.h"

#include <cassert>

#include <QKeyEvent>
#include <QFileDialog>

#include "brainweaverfile.h"
#include "qtbrainweaveraboutdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaverstudentstartcompletedialog.h"
#include "trace.h"
#include "ui_qtbrainweaverstudentmenudialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtStudentMenuDialog::QtStudentMenuDialog(const File file, QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtStudentMenuDialog),
    m_file(file)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help

  if (!m_file.GetStudentName().empty())
  {
    SetName(m_file.GetStudentName());
  }
  on_edit_name_textChanged(ui->edit_name->text());
}

ribi::braw::QtStudentMenuDialog::~QtStudentMenuDialog() noexcept
{
  delete ui;
}

std::string ribi::braw::QtStudentMenuDialog::GetName() const noexcept
{
  return ui->edit_name->text().toStdString();
}

void ribi::braw::QtStudentMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { on_button_save_clicked(); return; }
  QDialog::keyPressEvent(e);
}

void ribi::braw::QtStudentMenuDialog::on_button_about_clicked()
{
  ribi::braw::QtAboutDialog * const d = new ribi::braw::QtAboutDialog;
  assert(d);
  //const auto d(QtAboutDialog().Get());
  this->hide();
  d->exec();
  this->show();
}

void ribi::braw::QtStudentMenuDialog::on_button_quit_clicked()
{
  close();
}

void ribi::braw::QtStudentMenuDialog::on_button_start_clicked()
{
  m_file.SetStudentName(ui->edit_name->text().toStdString());
  QtStudentStartCompleteDialog d(m_file);
  this->ShowChild(&d);
}

void ribi::braw::QtStudentMenuDialog::on_edit_name_textChanged(const QString &arg1)
{
  //Enable start button when student has entered at least two characters
  assert(ui->edit_name->text() == arg1);
  if (arg1.size() > 1)
  {
    ui->button_start->setEnabled(true);
  }
  else
  {
    ui->button_start->setEnabled(false);
  }
}

void ribi::braw::QtStudentMenuDialog::on_button_save_clicked()
{
  const auto d = QtFileDialog::GetSaveFileDialog(QtFileDialog::FileType::cmp);
  d->setWindowTitle("Sla de concept map op");
  const int status = d->exec();
  if (status == QDialog::Rejected)
  {
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
}

void ribi::braw::QtStudentMenuDialog::Save(const std::string& filename)
{
  m_file.SetStudentName(ui->edit_name->text().toStdString());

  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == File::GetFilenameExtension()
    && "File must have correct file extension name");
  m_file.Save(filename);
  //{ const std::string debug_str = "File saved as " + filename; TRACE(debug_str); }
}

void ribi::braw::QtStudentMenuDialog::SetName(const std::string& name)
{
  ui->edit_name->setText(name.c_str());
}
