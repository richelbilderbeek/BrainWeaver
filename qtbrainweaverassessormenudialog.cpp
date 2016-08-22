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
#include "qtbrainweaverassessormenudialog.h"

#include <QFileDialog>
#include <QKeyEvent>

#include "qtbrainweaveraboutdialog.h"
//#include "brainweavermenudialog.h"
#include "qtconceptmaprateconceptdialognewname.h"
#include "qtbrainweavercreateassessmentcompletedialog.h"

#include "qtbrainweaverrateconceptmapdialog.h"
#include "qtbrainweaverfiledialog.h"
#include "trace.h"


#include "ui_qtbrainweaverassessormenudialog.h"
#pragma GCC diagnostic pop

ribi::braw::QtAssessorMenuDialog::QtAssessorMenuDialog(QWidget* parent)
  : QtDialog(parent),
    ui(new Ui::QtAssessorMenuDialog)
{
  ui->setupUi(this);
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); //Remove help
}

ribi::braw::QtAssessorMenuDialog::~QtAssessorMenuDialog() noexcept
{
  delete ui;
}

void ribi::braw::QtAssessorMenuDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key() == Qt::Key_Escape || (e->key() == Qt::Key_F4 && (e->modifiers() & Qt::AltModifier)))
  {
    emit remove_me(this);
    return;
  }
}

void ribi::braw::QtAssessorMenuDialog::on_button_create_assessment_clicked()
{
  QtCreateAssessmentCompleteDialog * const d = new QtCreateAssessmentCompleteDialog;
  emit add_me(d);
}


void ribi::braw::QtAssessorMenuDialog::on_button_about_clicked()
{
  ribi::braw::QtAboutDialog * const d{
    new ribi::braw::QtAboutDialog
  };
  assert(d);
  emit add_me(d);
}

void ribi::braw::QtAssessorMenuDialog::on_button_quit_clicked()
{
  emit remove_me(this);
}

void ribi::braw::QtAssessorMenuDialog::on_button_assess_result_clicked()
{
  //Load assessent file
  const auto d = QtFileDialog::GetOpenFileDialog();
  d->setWindowTitle("Kies een assessment bestand");
  const int status = d->exec();
  if (status == QDialog::Rejected) return;
  const auto v = d->selectedFiles();
  if (!v.isEmpty())
  {
    assert(v.size() == 1);
    const std::string filename = v[0].toStdString();
    File file = LoadFile(filename);
    QtRateConceptMapDialog * const d = new QtRateConceptMapDialog(file);
    emit add_me(d);
    //Will fail due to #85 at https://github.com/richelbilderbeek/Brainweaver/issues/85
    //The former architecture showed d modally, thus at this point d would have
    //a new file now. In this case, the file is read before modification
    file = d->GetFile();
  }
}
