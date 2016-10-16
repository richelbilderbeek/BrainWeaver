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

#include "qtbrainweaverfwd.h"
#include "brainweaverfile.h"
#include "qtbrainweaverdialog.h"

namespace Ui { class QtRateConceptMapDialog; }

namespace ribi {
namespace braw {

class QtRateConceptMapDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
  
public:
  using ConceptMap = cmap::QtConceptMap;
  explicit QtRateConceptMapDialog(
    const File& file,
    QWidget* parent = 0);
  QtRateConceptMapDialog(const QtRateConceptMapDialog&) = delete;
  QtRateConceptMapDialog& operator=(const QtRateConceptMapDialog&) = delete;
  ~QtRateConceptMapDialog() noexcept;

  const File& GetFile() const noexcept;
  cmap::QtConceptMap * GetWidget();

  ///Respond to key press
  void keyPressEvent(QKeyEvent *);

  void Save();
  void Save(const std::string& filename);

private slots:
  void changeEvent(QEvent *) override;
  void on_button_next_clicked();
  void on_button_save_clicked();
  void showEvent(QShowEvent *) override;

private:
  Ui::QtRateConceptMapDialog *ui;
  File m_file;
  ConceptMap * const m_concept_map;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERRATECONCEPTMAPDIALOG_H
