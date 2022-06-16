/**
 * @file example_test.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <cppunit/extensions/HelperMacros.h>

class ExampleTest : public CppUnit::TestFixture { 

  // Setup the test suite
  CPPUNIT_TEST_SUITE(ExampleTest);
  CPPUNIT_TEST(example_test_1);
  CPPUNIT_TEST(example_test_2);
  CPPUNIT_TEST_SUITE_END();

  private:

  public:
  void setUp() {
    // initialise test environment
  }

  void tearDown() {
    // clean up after test
  }


  void example_test_1() {
    int a = 1;
    int b = 2;

    CPPUNIT_ASSERT_EQUAL( a, 1 );
    CPPUNIT_ASSERT_EQUAL( b, 2 );
    CPPUNIT_ASSERT( a < b );
  }

  void example_test_2() {
    int a = 1;
    int b = 2;
    CPPUNIT_ASSERT( a > b );
  }
};


// register the test suite by name
CPPUNIT_TEST_SUITE_REGISTRATION(ExampleTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(ExampleTest, "example");
