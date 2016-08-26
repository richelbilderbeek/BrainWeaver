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
#ifndef QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_H
#define QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_H

#include "qtbrainweaverdialog.h"
#include "qtbrainweaverfwd.h"
#include "brainweaverfile.h"

namespace Ui {
  class QtPrintConceptMapDialog;
}

namespace ribi {
namespace braw {

///View the current work, optimized for humans
///This dialog will not be visible for humans at all in release
///QtPrintConceptMapDialog is optimized for printers
class QtPrintConceptMapDialog : public QtDialog
{
  Q_OBJECT //!OCLINT
  
public:
  using ConceptMap = cmap::QtConceptMap;
  ///file be const, as the Display Concept map cannot deal with const ribi::cmap::ConceptMap (yet?)
  explicit QtPrintConceptMapDialog(
    const File& file,
    QWidget *parent = 0
  );
  QtPrintConceptMapDialog(const QtPrintConceptMapDialog&) = delete;
  QtPrintConceptMapDialog& operator=(const QtPrintConceptMapDialog&) = delete;
  ~QtPrintConceptMapDialog() noexcept;
  void Print();

protected:
  void keyPressEvent(QKeyEvent * event);
  void resizeEvent(QResizeEvent *);
  void showEvent(QShowEvent *);

private slots:
  void on_button_print_clicked();
  void fitConceptMap();
private:
  Ui::QtPrintConceptMapDialog *ui;

  File m_file;

  ConceptMap * const m_widget;

  std::vector<QWidget *> CollectWidgets() const;

  friend class qtbrainweaverprintconceptmapdialog_test;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_H
