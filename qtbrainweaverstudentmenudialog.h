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
#ifndef QTBRAINWEAVERSTUDENTMENUDIALOG_H
#define QTBRAINWEAVERSTUDENTMENUDIALOG_H

#include "brainweaverfile.h"
#include "brainweaverfwd.h"
#include "qtbrainweaverdialog.h"

namespace Ui { class QtStudentMenuDialog; }

namespace ribi {
namespace braw {

class QtStudentMenuDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
    
  public:
  explicit QtStudentMenuDialog(const File file, QWidget* parent = 0);
  QtStudentMenuDialog(const QtStudentMenuDialog&) = delete;
  QtStudentMenuDialog& operator=(const QtStudentMenuDialog&) = delete;
  ~QtStudentMenuDialog() noexcept;

  ///Get the student his/her name
  std::string GetName() const noexcept;

  ///Save to file
  void Save(const std::string& filename);

  ///Set the student his/her name
  void SetName(const std::string& name);

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_start_clicked();

  void on_button_about_clicked();

  void on_button_quit_clicked();

  void on_edit_name_textChanged(const QString &arg1);

  void on_button_save_clicked();

private:
  Ui::QtStudentMenuDialog *ui;
  File m_file;

};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTMENUDIALOG_H
