/**
 * @file gdlparser_test.cpp
 *
 * Defining the tests for GDLParser.
 */


#define BOOST_TEST_MODULE GDLParserTest

#include <boost/version.hpp>

// We only need to do this for old Boost versions.
#if BOOST_VERSION < 103600
  #define BOOST_AUTO_TEST_MAIN
#endif

#include <boost/test/unit_test.hpp>
#include "old_boost_test_definitions.hpp"
