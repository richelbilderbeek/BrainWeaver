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
#ifndef QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_H
#define QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#include "brainweaverfile.h"
#include "brainweaverfwd.h"
#pragma GCC diagnostic pop

namespace Ui { class QtStudentStartCompleteDialog; }

namespace ribi {
namespace pvdb {

class QtStudentStartCompleteDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
    
  public:
  explicit QtStudentStartCompleteDialog(const File file, QWidget* parent = 0);
  QtStudentStartCompleteDialog(const QtStudentStartCompleteDialog&) = delete;
  QtStudentStartCompleteDialog& operator=(const QtStudentStartCompleteDialog&) = delete;
  ~QtStudentStartCompleteDialog() noexcept;

  ///Does the user need to go back to the student menu?
  bool GoBackToMenu() const { return m_back_to_menu; }

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_start_associate_clicked();

  void on_button_start_construct_clicked();

  private:
  Ui::QtStudentStartCompleteDialog *ui;

  ///Does the dialog want to go back to the student menu?
  bool m_back_to_menu;

  File m_file;

  ///Save to file
  void Save();
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTBRAINWEAVERSTUDENTSTARTCOMPLETEDIALOG_H
