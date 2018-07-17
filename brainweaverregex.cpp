#include "brainweaverregex.h"

#include <sstream>
#include "conceptmapregex.h"

#include "ribi_regex.h"

std::string ribi::braw::Regex::GetRegexAbout() const noexcept
{
  return GetRegexOfSomething("about");
}

std::string ribi::braw::Regex::GetRegexAssessorName() const noexcept
{
  return GetRegexOfSomething("assessor_name");
}

std::string ribi::braw::Regex::GetRegexCluster() const noexcept
{
  return GetRegexOfSomething("cluster");
}

std::string ribi::braw::Regex::GetRegexConcept() const noexcept
{
  return ribi::cmap::Regex().GetRegexConcept();
}

std::string ribi::braw::Regex::GetRegexConceptMap() const noexcept
{
  return ribi::cmap::Regex().GetRegexConceptMap();
}

std::string ribi::braw::Regex::GetRegexQuestion() const noexcept
{
  return GetRegexOfSomething("question");
}

std::string ribi::braw::Regex::GetRegexRating() const noexcept
{
  return GetRegexOfSomething("rating");
}

std::string ribi::braw::Regex::GetRegexRatingComplexity() const noexcept
{
  return GetRegexOfSomething("rating_complexity");
}

std::string ribi::braw::Regex::GetRegexRatingConcreteness() const noexcept
{
  return GetRegexOfSomething("rating_concreteness");
}

std::string ribi::braw::Regex::GetRegexRatingSpecificity() const noexcept
{
  return GetRegexOfSomething("rating_specificity");
}

std::string ribi::braw::Regex::GetRegexStudentName() const noexcept
{
  return GetRegexOfSomething("student_name");
}

std::string ribi::braw::Regex::GetRegexVersion() const noexcept
{
  return GetRegexOfSomething("version");
}

std::string ribi::braw::Regex::GetRegexOfSomething(
  const std::string& s
) const noexcept
{
  std::stringstream t;
  t << "(<" << s << ">.*?</" << s << ">)";
  return t.str();
}

/*
std::vector<std::string>
  ribi::braw::GetRegexMatches(
  const std::string& s,
  const std::string& regex_str
)
{
  return ribi::Regex().GetRegexMatches(s,regex_str);
}
*/
