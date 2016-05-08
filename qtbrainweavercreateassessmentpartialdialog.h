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
#ifndef QTBRAINWEAVERCREATEASSESSMENTPARTIALDIALOG_H
#define QTBRAINWEAVERCREATEASSESSMENTPARTIALDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
//#include <boost/shared_ptr.hpp>
#include <QDialog>
#include "brainweaverfwd.h"
#include "brainweaverfile.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtCreateAssessmentPartialDialog;
}

namespace ribi {

namespace pvdb {

class QtCreateAssessmentPartialDialog : public QDialog
{
    Q_OBJECT
    
  public:
  explicit QtCreateAssessmentPartialDialog(
    const File file,
    QWidget* parent = 0);
  QtCreateAssessmentPartialDialog(const QtCreateAssessmentPartialDialog&) = delete;
  QtCreateAssessmentPartialDialog& operator=(const QtCreateAssessmentPartialDialog&) = delete;
  ~QtCreateAssessmentPartialDialog() noexcept;

  private slots:
  void keyPressEvent(QKeyEvent* e);
  void on_button_save_clicked();

  void AnyEditChanged();

  private:
  Ui::QtCreateAssessmentPartialDialog *ui;
  File m_file;
};

} //~namespace pvdb

} //~namespace ribi

#endif // QTBRAINWEAVERCREATEASSESSMENTPARTIALDIALOG_H
