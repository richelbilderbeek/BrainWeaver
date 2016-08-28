//---------------------------------------------------------------------------
/*
Brainweaver, tool to create and assess concept maps
Copyright (C) 2012-2016 Richel Bilderbeek

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
#ifndef BRAINWEAVERHELPER_H
#define BRAINWEAVERHELPER_H

#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "brainweaverfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace braw {

///compleXity eStimated: X_s, a percentage, that will be shown at row = 0, col = 1
///x_s = ((2*n_relations_not_to_focus)/(n_nodes*(n_nodes-1))))^0.25*100%
///Estimated, thus needs no assessor, nor ratings
int CalculateComplexityEstimated(const File& file);

///Complexity experimental value: X_e at row = 0, col = 0
///50.0 * sum_rated_complexity / n_nodes
///Experimental, thus relies on rating by assessor
int CalculateComplexityExperimental(const File& file);

///Concreteness eStimated: C_s at row = 1, col = 1
///C_s = 100.0 * n_examples / (n_examples + n_nodes + n_relations_not_to_focus)
///Estimated, thus needs no assessor, nor ratings
int CalculateConcretenessEstimated(const File& file);

///Concreteness Experimental: C_e, a percentage that will be shown at row = 1, col = 0
///50.0 * sum_rated_concreteness / n_nodes
///Experimental, thus relies on rating by assessor
int CalculateConcretenessExperimental(const File& file);

///Richness Experimental, r_e, a percentage that will be shown at row = 3, col = 0
///r_e = ((a + b) / 14) * 100%
///a = number of different Competencies
///b = number of Competencies between 1/12th and 1/4th of number of examples
///Experimental, thus relies on rating by assessor
int CalculateRichnessExperimental(const File& file);

///Experimental specificity: s_e, a percentage that will be shown at row = 2, col = 0
///s_e = 50.0 * sum_rated_specificity / n_nodes
///Experimental, thus relies on rating by assessor
int CalculateSpecificityExperimental(const File& file);

///Undo a Wordwrap
std::string Unwordwrap(const std::vector<std::string>& v) noexcept;

///Wordwrap the text to obtain lines of max_len characters
///If the string _must_ be seperable by spaces;
///  a word can have a maximum length of max_len
std::vector<std::string> Wordwrap(
  const std::string& s, const std::size_t max_len
) noexcept;

} //~namespace braw
} //~namespace ribi

#endif // BRAINWEAVERHELPER_H
