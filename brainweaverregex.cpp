#include "brainweaverregex.h"

#include <sstream>
#include "conceptmapregex.h"

#include "ribi_regex.h"

std::string ribi::pvdb::Regex::GetRegexAbout() noexcept
{
  return GetRegexOfSomething("about");
  //return "(<about>.*?</about>)";
}

std::string ribi::pvdb::Regex::GetRegexAssessorName() noexcept
{
  return GetRegexOfSomething("assessor_name");
  //return "(<assessor_name>.*?</assessor_name>)";
}

std::string ribi::pvdb::Regex::GetRegexCluster() noexcept
{
  return GetRegexOfSomething("cluster");
  //return "(<cluster>.*?</cluster>)";
}

std::string ribi::pvdb::Regex::GetRegexConcept() noexcept
{
  return ribi::cmap::Regex().GetRegexConcept();
}

std::string ribi::pvdb::Regex::GetRegexConceptMap() noexcept
{
  return ribi::cmap::Regex().GetRegexConceptMap();
}

std::string ribi::pvdb::Regex::GetRegexQuestion() noexcept
{
  return GetRegexOfSomething("question");
}

std::string ribi::pvdb::Regex::GetRegexStudentName() noexcept
{
  return GetRegexOfSomething("student_name");
}

std::string ribi::pvdb::Regex::GetRegexVersion() noexcept
{
  return GetRegexOfSomething("version");
}

std::string ribi::pvdb::Regex::GetRegexOfSomething(const std::string& s) noexcept
{
  std::stringstream t;
  t << "(<" << s << ">.*?</" << s << ">)";
  return t.str();
}

std::vector<std::string>
  ribi::pvdb::Regex::GetRegexMatches(
  const std::string& s,
  const std::string& regex_str
)
{
  return ribi::Regex().GetRegexMatches(s,regex_str);
}
