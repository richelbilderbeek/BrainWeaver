#include "brainweaverregex.h"

#include <boost/test/unit_test.hpp>

#include "ribi_regex.h"

BOOST_AUTO_TEST_CASE(test_ribi_pvdb_regex_GetRegexMatches)
{
  const ribi::braw::Regex r;
  {
    const std::string s{"what /n I /t care /r about"};
    const std::string tag{"about"};
    const std::string junk{"gibberish, nonsense and \n hard \r \t characters"};
    const std::string t = junk + "<" + tag + ">" + s + "</" + tag + ">" + junk;
    const std::vector<std::string> expected = { "<" + tag + ">" + s + "</" + tag + ">" };
    const auto result = ::ribi::Regex().GetRegexMatches(t, r.GetRegexAbout());
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    assert(expected.size() == 1);
    BOOST_CHECK_EQUAL(result[0], expected[0]);
  }
  //Bug 2016-04-09
  {
    const std::string s =
      "<file><about>Brainweaver</about><assessor_name></assessor_name><cluster></cluster><conceptmap>digraph G {"
      "0[label=\"<node><concept><name>Focal$$$SPACE$$$question?</name><examples></examples><concept_is_complex>0</concept_is_complex><complexity>-1</complexity><concreteness>-1</concreteness><specificity>-1</specificity></concept><x>0</x><y>0</y><is_center_node>1</is_center_node></node>\", regular=\"0\"];"
      "}</conceptmap><question>Focal question?</question><student_name>Richel Bilderbeek</student_name><version>0.4</version></file>"
    ;
    const auto result = ::ribi::Regex().GetRegexMatches(s, r.GetRegexConceptMap());
    BOOST_CHECK_EQUAL(result.size(), 1);
  }
}
