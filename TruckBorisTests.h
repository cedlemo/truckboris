#ifndef TRUCKBORISTESTS_H
#define TRUCKBORISTESTS_H
#include "HeaderParser.h"
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <vector>
#include <iostream>

#define TEST_SOURCE_FILE "./data/test.cpp"
#define TEST_CLASS_SOURCE_FILE "./data/class.h"
#define STR_MESSASSERT(stdStr1, stdStr2)\
  CPPUNIT_ASSERT_MESSAGE(stdStr1, stdStr1 == stdStr2)
class TruckBorisDefaultConstructorTests: public CppUnit::TestFixture
{
  private:
    TruckBoris::HeaderParser * m_headerParser;
  public:
  void setUp()
  {
    m_headerParser = NULL;
    m_headerParser = new TruckBoris::HeaderParser();
  }
  void tearDown()
  {
    std::cout << "Delete start" << std::endl;
    if(m_headerParser)
      delete m_headerParser;
    std::cout << "Delete stop" << std::endl;
  }
  void headerParser_testEmptyHeaderParser()
  {
    std::cout << "test Empty Header" << std::endl;
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string() );
    CPPUNIT_ASSERT(m_headerParser->getHeadersPaths().size() == 0);
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
  }
  void headerParser_testAddGoodSourceFile()
  {
    std::cout << "test add good src file" << std::endl;
    m_headerParser->addSourceFile(std::string(TEST_SOURCE_FILE));
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
  } 
  void headerParser_testAddHeaderPath()
  {
    std::cout << "test add Header Path" << std::endl;
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    m_headerParser->addSearchPath(std::string("/usr/include"));
    std::vector<std::string> hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 1);
    STR_MESSASSERT(hp[0],std::string("/usr/include"));
  }
  void headerParser_testAddHeadersPaths()
  {
    std::cout << "test add Headers Paths" << std::endl;
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    std::vector<std::string> input;
    input.push_back(std::string("/usr/include/xcb"));
    input.push_back(std::string("/usr/include/thisisatest"));
    m_headerParser->addSearchPaths(input);
    std::vector<std::string> hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 3);
    STR_MESSASSERT(hp[2], std::string("/usr/include/thisisatest"));
    input.push_back(std::string("/usr/include/evas"));
    hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 4);
    STR_MESSASSERT(hp[0], std::string("/usr/include"));
    STR_MESSASSERT(hp[2], std::string("/usr/include/thisisatest"));
    STR_MESSASSERT(hp[3], std::string("/usr/include/evas"));
  }
  void headerParser_testParse()
  {
    std::cout << "test Parse" << std::endl;
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    m_headerParser->addSourceFile(TEST_SOURCE_FILE);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    std::vector<TruckBoris::Structure> structures;
    structures = m_headerParser->getStructures();
    CPPUNIT_ASSERT(structures.size() == 6 ); 
  }
  CPPUNIT_TEST_SUITE(TruckBorisDefaultConstructorTests);
  CPPUNIT_TEST(headerParser_testEmptyHeaderParser);
  CPPUNIT_TEST(headerParser_testAddGoodSourceFile);
  CPPUNIT_TEST(headerParser_testAddHeaderPath);
  CPPUNIT_TEST(headerParser_testParse);
  CPPUNIT_TEST_SUITE_END();
};
#endif
