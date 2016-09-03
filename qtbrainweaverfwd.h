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
#ifndef QTBRAINWEAVERFWD_H
#define QTBRAINWEAVERFWD_H

#include "brainweaverfwd.h"
#include "qtconceptmapfwd.h"

struct QRegExp;
struct QTimer;

namespace ribi {
namespace braw {

struct QtArrow;
struct QtClusterDialog;
struct QtClusterWidget;
struct QtConceptMapDialog;
struct QtStudentMenuDialog;

} //~namespace braw

struct QtArrowItem;
struct QtQuadBezierArrowItem;

} //~namespace ribi

#endif // QTBRAINWEAVERFWD_H
