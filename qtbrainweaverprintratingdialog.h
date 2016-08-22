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
#ifndef QTBRAINWEAVERPRINTRATINGDIALOG_H
#define QTBRAINWEAVERPRINTRATINGDIALOG_H

#include "qtbrainweaverdialog.h"
#include "qtbrainweaverfwd.h"
#include "brainweaverfile.h"

namespace Ui {
  class QtPrintRatingDialog;
}

struct QTableWidget;

namespace ribi {
namespace braw {

///View the current rating, optimized for printers
///This dialog will not be visible for humans at all in release
///QtRatingDialog is optimized for humans
class QtPrintRatingDialog : public QtDialog
{
  Q_OBJECT
  
public:
  ///file be const, as the Display Concept map cannot deal with const ribi::cmap::ConceptMap (yet?)
  explicit QtPrintRatingDialog(
    const File& file,
    QWidget *parent = 0);
  QtPrintRatingDialog(const QtPrintRatingDialog&) = delete;
  QtPrintRatingDialog& operator=(const QtPrintRatingDialog&) = delete;
  ~QtPrintRatingDialog() noexcept;

  QTableWidget * GetTableConcepts();
  QTableWidget * GetTableExamples();
  QTableWidget * GetTableValues();
  QTableWidget * GetTableMiscValues();
  void Print();

protected:
  void keyPressEvent(QKeyEvent * event);
  void showEvent(QShowEvent *);

private slots:
  void on_button_print_clicked();
  const std::vector<QWidget *> CollectWidgets() const;
private:
  Ui::QtPrintRatingDialog *ui;

  ///m_file be const, as the Display Concept map cannot deal with const ribi::cmap::ConceptMap (yet?)
  const File m_file;

  cmap::QtConceptMap * const m_widget;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERPRINTRATINGDIALOG_H
