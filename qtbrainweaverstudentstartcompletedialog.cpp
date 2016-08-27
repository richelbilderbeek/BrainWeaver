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
#include "qtbrainweaverstudentstartcompletedialog.h"

#include <fstream>
#include <QKeyEvent>
#include <QFileDialog>
#include "brainweaverfile.h"
#include "brainweaverclusterfactory.h"
#include "conceptmapfactory.h"
//#include "brainweavermenudialog.h"
#include "qtbrainweaverfiledialog.h"
#include "qtbrainweaverclusterdialog.h"
#include "qtbrainweaverconceptmapdialog.h"

#include "trace.h"
#include "ui_qtbrainweaverstudentstartcompletedialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtStudentStartCompleteDialog::QtStudentStartCompleteDialog(
  const File file,
  QWidget* parent)
  : QtDialog(parent),
    ui(new Ui::QtStudentStartCompleteDialog),
    m_back_to_menu(false),
    m_file(file)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
}

ribi::braw::QtStudentStartCompleteDialog::~QtStudentStartCompleteDialog() noexcept
{
  delete ui;
}

void ribi::braw::QtStudentStartCompleteDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { emit remove_me(this); return; }
  if ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_S) { Save(); return; }
  QDialog::keyPressEvent(e);
}

void ribi::braw::QtStudentStartCompleteDialog::on_button_start_associate_clicked()
{
  QtClusterDialog * const d{
    new QtClusterDialog(m_file)
  };
  emit add_me(d);

  //Will fail due to #85 at https://github.com/richelbilderbeek/Brainweaver/issues/85
  //The former architecture showed d modally, thus at this point d would have
  //a new file now. In this case, the file is read before modification
  if (d->GoBackToMenu())
  {
    m_back_to_menu = true;
    emit remove_me(this);
  }
}

void ribi::braw::QtStudentStartCompleteDialog::on_button_start_construct_clicked()
{
  QtConceptMapDialog * const d{
    new QtConceptMapDialog(m_file)
  };
  emit add_me(d);

  //Will fail due to #85 at https://github.com/richelbilderbeek/Brainweaver/issues/85
  //The former architecture showed d modally, thus at this point d would have
  //a new file now. In this case, the file is read before modification
  if (d->GoBackToMenu())
  {
    m_back_to_menu = true;
    emit remove_me(this);
  }
}

void ribi::braw::QtStudentStartCompleteDialog::Save()
{
  const auto d = QtFileDialog().GetSaveFileDialog(QtFileDialog::FileType::cmp);
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
    =  (filename_raw.size() < GetFilenameExtension().size()
      || filename_raw.substr( filename_raw.size() - 3, 3 ) != GetFilenameExtension()
     ? filename_raw + "." + GetFilenameExtension()
     : filename_raw);
  assert(filename.size() > 3
    && filename.substr( filename.size() - 3, 3 ) == GetFilenameExtension()
    && "File must have correct file extension name");
  m_file.Save(filename);
  { const std::string debug_str = "File saved as " + filename; TRACE(debug_str); }
}
