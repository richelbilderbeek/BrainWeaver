#ifndef BRAINWEAVER_REGEX_H
#define BRAINWEAVER_REGEX_H

#include <string>
#include <vector>

namespace ribi {
namespace pvdb {

class Regex
{
public:
  static std::string GetRegexAbout() noexcept;
  static std::string GetRegexAssessorName() noexcept;
  static std::string GetRegexCluster() noexcept;
  static std::string GetRegexConcept() noexcept;
  static std::string GetRegexConceptMap() noexcept;
  static std::string GetRegexQuestion() noexcept;
  static std::string GetRegexStudentName() noexcept;
  static std::string GetRegexVersion() noexcept;

  ///Forwards to Ribi.Regex
  static std::vector<std::string>
    GetRegexMatches(
    const std::string& s,
    const std::string& regex_str
  );

private:
  static std::string GetRegexOfSomething(const std::string& s) noexcept;
};

} //~namespace pvdb
} //~namespace ribi


#endif // BRAINWEAVER_REGEX_H
