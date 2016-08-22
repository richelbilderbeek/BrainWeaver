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
#ifndef QTBRAINWEAVEROVERVIEWWIDGET_H
#define QTBRAINWEAVEROVERVIEWWIDGET_H

#include "qtbrainweaverdialog.h"
#include <QGraphicsView>
#include "brainweaverfwd.h"


namespace ribi {
namespace braw {

struct QtDialog;

class QtOverviewWidget : public QGraphicsView
{
  Q_OBJECT

public:

  explicit QtOverviewWidget(QWidget* parent = 0);
    
public slots:

  void mouseDoubleClickEvent(QMouseEvent *event);

private:

  ///Create all dialogs
  static std::vector<QDialog* > GetAllDialogs();

  ///NASTY BUG ALERT: It crashes Wine if m_dialogs is created as
  ///const std::vector<boost::shared_ptr<QDialog> > m_dialogs;
  ///No idea why...
  const std::vector<QDialog* > m_dialogs;

};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVEROVERVIEWWIDGET_H
