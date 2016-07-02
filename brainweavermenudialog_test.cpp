#include "brainweavermenudialog.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_ribi_brainweaver_menu)
{
  ribi::braw::MenuDialog d;
  BOOST_CHECK(d.Execute( {} ) ==  0);
  BOOST_CHECK(d.Execute( { "test" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--about" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--help" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--history" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--license" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--version" } ) == 0);
}
