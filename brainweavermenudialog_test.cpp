#include "brainweavermenudialog.h"
#include <iostream>
#include <sstream>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_ribi_brainweaver_menu)
{
  //Redirect from https://stackoverflow.com/a/8246536
  std::streambuf *old = std::cout.rdbuf(); // <-- save
  std::stringstream ss;
  std::cout.rdbuf(ss.rdbuf()); // <-- redirect

  ribi::braw::MenuDialog d;
  BOOST_CHECK(d.Execute( {} ) ==  0);
  BOOST_CHECK(d.Execute( { "test" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--about" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--helrp" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--history" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--license" } ) == 0);
  BOOST_CHECK(d.Execute( { "test", "--version" } ) == 0);

  std::cout.rdbuf(old); // <-- restore
}
