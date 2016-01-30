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

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
//#include <boost/shared_ptr.hpp>

#include "qtbrainweaverfwd.h"
#include "qthideandshowdialog.h"
#include "brainweaverfile.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtPvdbPrintConceptMapDialog;
}

namespace ribi {

namespace pvdb {

///View the current work, optimized for humans
///This dialog will not be visible for humans at all in release
///QtPvdbPrintConceptMapDialog is optimized for printers
class QtPvdbPrintConceptMapDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT
  
public:
  using ConceptMap = cmap::QtConceptMap;
  ///file be const, as the Display Concept map cannot deal with const ribi::cmap::ConceptMap (yet?)
  explicit QtPvdbPrintConceptMapDialog(
    const File& file,
    QWidget *parent = 0
  );
  QtPvdbPrintConceptMapDialog(const QtPvdbPrintConceptMapDialog&) = delete;
  QtPvdbPrintConceptMapDialog& operator=(const QtPvdbPrintConceptMapDialog&) = delete;
  ~QtPvdbPrintConceptMapDialog() noexcept;
  void Print();

protected:
  void keyPressEvent(QKeyEvent * event);
  void resizeEvent(QResizeEvent *);
  void showEvent(QShowEvent *);

private slots:
  void on_button_print_clicked();
  void fitConceptMap();
private:
  Ui::QtPvdbPrintConceptMapDialog *ui;

  ///m_file be const, as the Display Concept map cannot deal with const ribi::cmap::ConceptMap (yet?)
  File m_file;

  ConceptMap * const m_widget;

  const std::vector<QWidget *> CollectWidgets() const;



};

} //~namespace pvdb

} //~namespace ribi

#endif // QTBRAINWEAVERPRINTCONCEPTMAPDIALOG_H
