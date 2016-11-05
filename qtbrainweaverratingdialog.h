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
#ifndef QTBRAINWEAVERRATINGDIALOG_H
#define QTBRAINWEAVERRATINGDIALOG_H

#include <iosfwd>
#include "brainweaverfile.h"
#include "brainweaverfwd.h"
#include "qtbrainweaverdialog.h"

namespace Ui { class QtRatingDialog; }

struct QTableWidget;

namespace ribi {
namespace braw {

///View the current rating, optimized for humans
///QtPrintRatingDialog is optimized for printers
class QtRatingDialog : public QtDialog
{
  Q_OBJECT //!OCLINT

  public:
  explicit QtRatingDialog(const File file, QWidget* parent = 0);
  QtRatingDialog(const QtRatingDialog&) = delete;
  QtRatingDialog& operator=(const QtRatingDialog&) = delete;
  ~QtRatingDialog() noexcept;

  bool GetBackToMenu() const noexcept;
  void Save(const std::string& filename) const;

  private slots:
  void on_button_save_clicked();
  void keyPressEvent(QKeyEvent* e);
  void on_button_print_clicked();
  void on_edit_name_textEdited(const QString &arg1);
  void showEvent(QShowEvent *);

private:
  Ui::QtRatingDialog *ui;
  bool m_back_to_menu;
  File m_file;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERRATINGDIALOG_H
