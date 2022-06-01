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