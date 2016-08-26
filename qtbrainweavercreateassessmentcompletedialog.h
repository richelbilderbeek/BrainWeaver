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
#ifndef QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_H
#define QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_H

#include "qtbrainweaverdialog.h"
#include "brainweaverfwd.h"

namespace Ui { class QtCreateAssessmentCompleteDialog; }

namespace ribi {
namespace braw {

class QtCreateAssessmentCompleteDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
    
  public:
  explicit QtCreateAssessmentCompleteDialog(QWidget* parent = 0);
  QtCreateAssessmentCompleteDialog(const QtCreateAssessmentCompleteDialog&) = delete;
  QtCreateAssessmentCompleteDialog& operator=(const QtCreateAssessmentCompleteDialog&) = delete;
  ~QtCreateAssessmentCompleteDialog() noexcept;

  ///Get the filled in concept map focal question
  std::string GetQuestion() const noexcept;

  ///Must the parent go back to the menu?
  bool GoBackToMenu() const noexcept { return m_back_to_menu; }

  ///Save file to disk
  void Save(const std::string& filename) const;

  ///Fill in the concept map focal question
  void SetQuestion(const std::string& question);

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_save_clicked();

  void on_edit_textChanged(const QString &arg1);

private:
  Ui::QtCreateAssessmentCompleteDialog *ui;

  ///Must the parent go back to the menu?
  bool m_back_to_menu;
};

} //~namespace braw
} //~namespace ribi

#endif // QTBRAINWEAVERCREATEASSESSMENTCOMPLETEDIALOG_H
