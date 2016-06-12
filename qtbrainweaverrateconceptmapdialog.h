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
#ifndef QTBRAINWEAVERRATECONCEPTMAPDIALOG_H
#define QTBRAINWEAVERRATECONCEPTMAPDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#include "qtbrainweaverfwd.h"
#include "brainweaverfile.h"
#pragma GCC diagnostic pop

namespace Ui { class QtRateConceptMapDialog; }

namespace ribi {
namespace braw {

class QtRateConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  using ConceptMap = cmap::QtConceptMap;
  explicit QtRateConceptMapDialog(
    const File& file,
    QWidget* parent = 0);
  QtRateConceptMapDialog(const QtRateConceptMapDialog&) = delete;
  QtRateConceptMapDialog& operator=(const QtRateConceptMapDialog&) = delete;
  ~QtRateConceptMapDialog() noexcept;

  cmap::QtConceptMap * GetWidget();

  File GetFile() const noexcept { return m_file; }

  ///Respond to key press
  void keyPressEvent(QKeyEvent *);

  void Save();
  void Save(const std::string& filename);

private slots:
  void on_button_next_clicked();

  void on_button_save_clicked();

private:
  Ui::QtRateConceptMapDialog *ui;
  File m_file;
  ConceptMap * const m_concept_map;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERRATECONCEPTMAPDIALOG_H
