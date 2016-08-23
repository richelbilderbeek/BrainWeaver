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
#ifndef QTBRAINWEAVERCONCEPTMAPDIALOG_H
#define QTBRAINWEAVERCONCEPTMAPDIALOG_H

#include "qtconceptmap.h"
#include "brainweaverfile.h"
#include "qtbrainweaverdialog.h"
#include "conceptmap.h"

namespace Ui { class QtConceptMapDialog; }

namespace ribi {
namespace braw {

class QtConceptMapDialog : public QtDialog
{
  Q_OBJECT
    
  public:
  explicit QtConceptMapDialog(const File& file, QWidget* parent = 0);
  QtConceptMapDialog(const QtConceptMapDialog&) = delete;
  QtConceptMapDialog& operator=(const QtConceptMapDialog&) = delete;
  ~QtConceptMapDialog() noexcept;

  ///Obtain the widget
  const ribi::cmap::QtConceptMap * GetWidget() const;
  ribi::cmap::QtConceptMap * GetWidget();

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const noexcept { return m_back_to_menu; }

  ///Update concept map into file
  void UpdateFileWithConceptMapFromWidget();

  ///Save to disk
  void Save(const std::string& filename) const;

  private slots:

  void keyPressEvent(QKeyEvent *);
  void on_autosave() noexcept;
  void on_button_save_clicked();
  void on_button_print_clicked();

private:
  Ui::QtConceptMapDialog *ui;

  ///Must we go back to the student menu?
  bool m_back_to_menu;

  ///The file
  File m_file;

  ///The concept map widget
  ribi::cmap::QtConceptMap * const m_widget;
};

///Create a concept map from a cluster
ribi::cmap::ConceptMap CreateFromCluster(
  const std::string& question,
  const Cluster& cluster
);

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCONCEPTMAPDIALOG_H
