#ifndef BRAINWEAVERHELPER_H
#define BRAINWEAVERHELPER_H

#include <string>
#include <vector>




#include "brainweaverfwd.h"


namespace ribi {
namespace braw {

///Complexity experimental value: X_e at row = 0, col = 0
///50.0 * sum_rated_complexity / n_nodes
///Experimental, thus relies on rating by assessor
int CalculateComplexityExperimental(const File& file);

///Concreteness Experimental: C_e, a percentage that will be shown at row = 1, col = 0
///50.0 * sum_rated_concreteness / n_nodes
///Experimental, thus relies on rating by assessor
int CalculateConcretenessExperimental(const File& file);

///Richness Experimental, r_e, a percentage that will be shown at row = 3, col = 0
///r_e = ((a + b) / 14) * 100%
///a = number of different Competencies
///b = number of Competencies between 1/12th and 1/4th of number of examples
///Experimental, thus relies on rating by assessor
int CalculateRichness(const File& file);

///Experimental specificity: s_e, a percentage that will be shown at row = 2, col = 0
///s_e = 50.0 * sum_rated_specificity / n_nodes
///Experimental, thus relies on rating by assessor
int CalculateSpecificityExperimental(const File& file);

///Does the file has some concept examples that are not rated yet?
bool HasUnitializedExamples(const File& file) noexcept;

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
