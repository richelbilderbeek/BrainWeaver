#include "brainweavercluster.h"
#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "conceptmapcompetency.h"
#include "brainweavercluster.h"
#include "brainweaverclusterfactory.h"
#include "brainweaverhelper.h"
#include "conceptmapconcept.h"
#include "conceptmapexamples.h"
#include "conceptmapexample.h"
#include "conceptmapconceptfactory.h"
#include "conceptmaphelper.h"
#include "testtimer.h"
#include "trace.h"

using namespace ribi::cmap;
using namespace ribi::braw;

BOOST_AUTO_TEST_CASE(ribi_pvdb_cluster_test)
{
  //Test operator== and operator!=
  {
    const auto tmp_tests_1 = ClusterFactory().GetTests();
    const int sz = static_cast<int>(tmp_tests_1.size());
    for (int i=0; i!=sz; ++i)
    {
      const auto tmp_tests_a = ClusterFactory().GetTests(); //For crosscompiler
      const Cluster a = tmp_tests_a.at(i);
      const auto tmp_tests_b = ClusterFactory().GetTests(); //For crosscompiler
      Cluster b = tmp_tests_b.at(i);
      BOOST_CHECK(a == a);
      BOOST_CHECK(a == b);
      BOOST_CHECK(b == a);
      BOOST_CHECK(b == b);
      for (int j=0; j!=sz; ++j)
      {
        const auto tmp_tests_c = ClusterFactory().GetTests(); //For crosscompiler
        const auto tmp_tests_d = ClusterFactory().GetTests(); //For crosscompiler
        const Cluster c = tmp_tests_c.at(j);
        Cluster d = tmp_tests_d.at(j);
        BOOST_CHECK(c == c);
        BOOST_CHECK(c == d);
        BOOST_CHECK(d == c);
        BOOST_CHECK(d == d);
        if (i==j)
        {
          BOOST_CHECK(a == c);
          BOOST_CHECK(a == d);
          BOOST_CHECK(b == c);
          BOOST_CHECK(b == d);
        }
        else
        {
          BOOST_CHECK(i!=j);
          BOOST_CHECK(a != c);
          BOOST_CHECK(a != d);
          BOOST_CHECK(b != c);
          BOOST_CHECK(b != d);
        }
      }
    }
  }
}

BOOST_AUTO_TEST_CASE(ribi_pvdb_cluster_to_xml_and_back)
{
  //Empty cluster
  {
    const Cluster c;
    const std::string s = ToXml(c);
    const auto d = XmlToCluster(s);
    BOOST_CHECK_EQUAL(c, d);
  }
  //Cluster with one concept without examples
  {
    const Cluster c( { Concept("A") } );
    const std::string s = ToXml(c);
    const auto d = XmlToCluster(s);
    BOOST_CHECK_EQUAL(c, d);
  }
  //Cluster with one concept with one example
  {
    const Cluster c( { Concept("A", Examples( {Example("1") } )) } );
    const std::string s = ToXml(c);
    const auto d = XmlToCluster(s);
    BOOST_CHECK_EQUAL(c, d);
  }
  //Cluster with one concept with two examples
  {
    const Cluster c(
      {
        Concept("A", Examples( { Example("1"), Example("2") } ))
      }
    );
    const std::string s = ToXml(c);
    const auto d = XmlToCluster(s);
    BOOST_CHECK_EQUAL(c, d);
  }
  //Cluster with two concepts without examples
  {
    const Cluster c(
      {
        Concept("A"),
        Concept("B")
      }
    );
    const std::string s = ToXml(c);
    const auto d = XmlToCluster(s);
    BOOST_CHECK_EQUAL(c, d);
  }
  //Cluster with two concepts with one example
  {
    const Cluster c(
      {
        Concept("A", Examples( {Example("1") } )),
        Concept("B", Examples( {Example("2") } ))
      }
    );
    const std::string s = ToXml(c);
    const auto d = XmlToCluster(s);
    BOOST_CHECK_EQUAL(c, d);
  }
  //Cluster with two concepts with two examples
  {
    const Cluster c(
      {
        Concept("A", Examples( { Example("1"), Example("2") } )),
        Concept("B", Examples( { Example("3"), Example("4") } ))
      }
    );
    const std::string s = ToXml(c);
    const auto d = XmlToCluster(s);
    BOOST_CHECK_EQUAL(c, d);
  }
}

BOOST_AUTO_TEST_CASE(ribi_pvdb_cluster_to_stream)
{
  //Empty cluster gives empty string
  {
    const Cluster c;
    std::stringstream s;
    s << c;
    BOOST_CHECK(s.str().empty());
  }
  //Cluster with one concept gives string
  {
    const Cluster c( { Concept("A") } );
    std::stringstream s;
    s << c;
    BOOST_CHECK(!s.str().empty());
  }
}
