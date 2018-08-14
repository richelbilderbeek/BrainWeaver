#include "brainweaverhelper.h"

#include <boost/test/unit_test.hpp>
#include "brainweaverfile.h"
#include "brainweaverfilefactory.h"

using namespace ribi::braw;

BOOST_AUTO_TEST_CASE(test_ribi_braw_helper_CalculateComplexityExperimental)
{
  const auto file = ribi::braw::FileFactory().Get5();
  const int result = ribi::braw::CalculateComplexityExperimental(file);
  BOOST_CHECK(result >= 0);
  BOOST_CHECK(result <= 100);
}

BOOST_AUTO_TEST_CASE(test_ribi_braw_helper_CalculateConcretenessExperimental)
{
  const auto file = ribi::braw::FileFactory().Get5();
  const int result = ribi::braw::CalculateConcretenessExperimental(file);
  BOOST_CHECK(result >= 0);
  BOOST_CHECK(result <= 100);
}

BOOST_AUTO_TEST_CASE(test_ribi_CalculateRichness_throws_on_incomplete_concept_map)
{
  const auto file = ribi::braw::FileFactory().Get5();
  assert(HasUnitializedExamples(file));
  BOOST_CHECK_THROW(
    ribi::braw::CalculateRichness(file),
    std::invalid_argument
  );

}

BOOST_AUTO_TEST_CASE(test_ribi_braw_helper_CalculateRichness)
{
  const auto file = ribi::braw::FileFactory().GetWithExamplesWithCompetencies(
     {
       ribi::cmap::Competency::organisations,
       ribi::cmap::Competency::profession
     }
  );
  assert(!HasUnitializedExamples(file));
  const int result = ribi::braw::CalculateRichness(file);
  BOOST_CHECK(result >= 0);
  BOOST_CHECK(result <= 100);
}

BOOST_AUTO_TEST_CASE(test_ribi_braw_helper_CalculateSpecificityExperimental)
{
  const auto file = ribi::braw::FileFactory().Get5();
  const int result = ribi::braw::CalculateSpecificityExperimental(file);
  BOOST_CHECK(result >= 0);
  BOOST_CHECK(result <= 100);
}

BOOST_AUTO_TEST_CASE(test_ribi_braw_helper_Unwordwrap)
{
  const std::vector<std::string> v = { "<text>", "Hello world", "</text>"};
  const auto s = ribi::braw::Unwordwrap(v);
  const std::string expected = "<text>Hello world</text>";
  BOOST_CHECK(s == expected);
}


BOOST_AUTO_TEST_CASE(test_ribi_braw_helper_Wordwrap)
{
  using namespace ribi::braw;
  {
    const auto v = {
      "",
      "1",
      "12",
      "123",
      "1234",
      "12345",
      "123456",
      "1234567",
      "12345678",
      "123456789",
      "1234567890",
      "12345678901",
      "123456789012",
      "1234567890123",
      "12345678901234",
      "123456789012345",
      "1234567890123456",
      "12345678901234567",
      "123456789012345678",
      "1234567890123456789",
      "12345678901234567890",
      "123456789012345678901",
      "1234567890123456789012",
      "12345678901234567890123",
      "123456789012345678901234",
      "1234567890123456789012345",
      "12345678901234567890123456",
      "123456789012345678901234567",
      "1234567890123456789012345678",
      "12345678901234567890123456789",
      "123456789012345678901234567890",
      "1234567890123456789012345678901",
      "12345678901234567890123456789012",
      "123456789012345678901234567890123",
      "1234567890123456789012345678901234",
      "12345678901234567890123456789012345",
      "123456789012345678901234567890123456",
      "1234567890123456789012345678901234567",
      "12345678901234567890123456789012345678",
      "123456789012345678901234567890123456789",
      "1234567890123456789012345678901234567890",
      "1 1",
      "12 12",
      "123 123",
      "1234 1234",
      "12345 12345",
      "123456 123456",
      "1234567 1234567",
      "12345678 8",
      "123456789 9",
      "1234567890 0",
      "1234567890 1234567890",
      "1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      "1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890 1234567890",
      " 1",
      "  1",
      "  1 ",
      "  1  ",
      "  1 2 ",
      "  1 23 ",
      "  12 34  ",
      "  12  34  ",
      "   12   34   ",
      "   12   34   5",
      "   12   34   5 ",
      "   12   34   5 6",
      "0   12   34   5 6",
      "0   12   34   5 6  ",
      "                    ",
      "                      ",
      "                        ",
      "                            ",
      "                                    ",
      "                                                    ",
      "                                                                                     "
    };
    for (int len=1; len!=1000; ++len)
    {
      for (const std::string& s: v)
      {
        //Wordwrap calls Unwordwrap
        Wordwrap(s,len);
      }
    }
  }
}

