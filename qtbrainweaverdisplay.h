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
#ifndef QTBRAINWEAVERDISPLAY_H
#define QTBRAINWEAVERDISPLAY_H

#include "brainweaverfwd.h"

struct QTableWidget;

namespace ribi {

namespace braw {

///Functions for printing
struct QtDisplay
{
  QtDisplay();

  void DisplayRatedConcepts(const File& file,QTableWidget * const table) const;
  void DisplayExamples(const File& file, QTableWidget * const table) const;
  void DisplayValues(const File& file, QTableWidget * const table) const;
  void DisplayMiscValues(const File& file, QTableWidget * const table) const;

  private:

  ///Richness Experimental, r_e, a percentage that will be shown at row = 3, col = 0
  ///r_e = ((a + b) / 14) * 100%
  ///a = number of different Competencies
  ///b = number of Competencies between 1/12th and 1/4th of number of examples
  int CalculateRichnessExperimental(const File& file) const;

  ///Experimental specificity: s_e, a percentage that will be shown at row = 2, col = 0
  ///s_e = 50.0 * sum_rated_specificity / n_nodes
  int CalculateSpecificityExperimental(const File& file) const;

  ///Put number of nodes at cell (0,0) of table
  void SetNumberOfNodes(const File& file, QTableWidget * const table) const;
};

} //~namespace braw

} //~namespace ribi

#endif // QTBRAINWEAVERDISPLAY_H
