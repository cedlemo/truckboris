#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include "HeaderParser.h"
#include "TruckBorisTests.h"

#include <cppunit/extensions/HelperMacros.h>
CPPUNIT_TEST_SUITE_REGISTRATION(TruckBorisDefaultConstructorTests);
CPPUNIT_TEST_SUITE_REGISTRATION(TruckBorisSecondConstructorTests);
CPPUNIT_TEST_SUITE_REGISTRATION(TruckBorisParsingTests);
CPPUNIT_TEST_SUITE_REGISTRATION(TruckBorisCppParsingTests);
int main(int argc, char **argv)
{
  bool successfull = false;
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  runner.addTest(registry.makeTest());
  successfull = runner.run();
  return successfull;
}
