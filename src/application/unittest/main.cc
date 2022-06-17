/**
 * @file main.cc
 * @author Alec Turner (alec.turner8@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-16
 * 
 * @copyright Copyright (c) 2022
 * 
 * @brief Main file for the unittest application.
 *
 * The unittest application uses the CPPUnit framework to run unit tests. This
 * file defines a TestRunner instance and loads in a TestFactoryRegistry,
 * optionally taking a test registry name as a command line argument if a
 * subset of tests is desired.
 */
#include <stdio.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


int main(int argc, char **argv) {

  // initialise test runner
  CppUnit::TextUi::TestRunner runner;
  bool result;

  // check for test name in command line args
  if ( argc > 1 ){
    printf("Running test suite: %s\n", argv[1]);
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry(argv[1]);
    runner.addTest(registry.makeTest());
    result = runner.run(argv[1], false);

  }else{
    printf("Running all tests\n");
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    result = runner.run("", false);
  }

  if( result )
    return 0;
  else
    return 1;
}