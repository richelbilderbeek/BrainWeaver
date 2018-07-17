#ifndef BRAINWEAVER_REGEX_H
#define BRAINWEAVER_REGEX_H

#include <string>
#include <vector>

namespace ribi {
namespace braw {

class Regex
{
public:
  Regex() {}
  std::string GetRegexAbout() const noexcept;
  std::string GetRegexAssessorName() const noexcept;
  std::string GetRegexCluster() const noexcept;
  std::string GetRegexConcept() const noexcept;
  std::string GetRegexConceptMap() const noexcept;
  std::string GetRegexQuestion() const noexcept;
  std::string GetRegexRating() const noexcept;
  std::string GetRegexRatingComplexity() const noexcept;
  std::string GetRegexRatingConcreteness() const noexcept;
  std::string GetRegexRatingSpecificity() const noexcept;
  std::string GetRegexStudentName() const noexcept;
  std::string GetRegexVersion() const noexcept;

private:
  std::string GetRegexOfSomething(const std::string& s) const noexcept;
};

///Forwards to Ribi.Regex
//std::vector<std::string>
//  GetRegexMatches(
//  const std::string& s,
//  const std::string& regex_str
//);

} //~namespace braw
} //~namespace ribi


#endif // BRAINWEAVER_REGEX_H
