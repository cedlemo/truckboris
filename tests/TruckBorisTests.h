#ifndef TRUCKBORISTESTS_H
#define TRUCKBORISTESTS_H
#include "../src/HeaderParser.h"
#include <cppunit/extensions/HelperMacros.h>
#include <string>
#include <vector>
#include <iostream>

#define TEST_SOURCE_FILE "./data/test.cpp"
#define TEST_CLASS_SOURCE_FILE "./data/class.h"
#define TEST_LIMIT_PARSING_SOURCE_FILE "./data/test.c"
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
    if(m_headerParser)
      delete m_headerParser;
  }
  void headerParser_testEmptyHeaderParser()
  {
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string() );
    CPPUNIT_ASSERT(m_headerParser->getHeadersPaths().size() == 0);
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
  }
  void headerParser_testAddGoodSourceFile()
  {
    m_headerParser->addSourceFile(std::string(TEST_SOURCE_FILE));
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
  } 
  void headerParser_testAddHeaderPath()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    m_headerParser->addSearchPath(std::string("/usr/include"));
    std::vector<std::string> hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 1);
    STR_MESSASSERT(hp[0],std::string("/usr/include"));
  }
  void headerParser_testAddHeadersPaths()
  {
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
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    m_headerParser->addSourceFile(TEST_SOURCE_FILE);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    CPPUNIT_ASSERT(m_headerParser->nbStructures() == 6 ); 
  }
  CPPUNIT_TEST_SUITE(TruckBorisDefaultConstructorTests);
  CPPUNIT_TEST(headerParser_testEmptyHeaderParser);
  CPPUNIT_TEST(headerParser_testAddGoodSourceFile);
  CPPUNIT_TEST(headerParser_testAddHeaderPath);
  CPPUNIT_TEST(headerParser_testParse);
  CPPUNIT_TEST_SUITE_END();
};
class TruckBorisSecondConstructorTests: public CppUnit::TestFixture
{
  private:
    TruckBoris::HeaderParser * m_headerParser;
  public:
  void setUp()
  {
    m_headerParser = NULL;
    std::vector<std::string> hp;
    hp.push_back(std::string("/usr/include"));
    hp.push_back(std::string("/usr/include/thisisatest"));
    hp.push_back(std::string("/usr/include/evas-1"));
    m_headerParser = new TruckBoris::HeaderParser(std::string(TEST_SOURCE_FILE),hp);
  }
  void tearDown()
  {
    if(m_headerParser)
    delete m_headerParser;
  }
  void headerParser_testInitializedHeaderParser()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    std::vector<std::string> hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 3);
    STR_MESSASSERT(hp[0], std::string("/usr/include"));
    STR_MESSASSERT(hp[1], std::string("/usr/include/thisisatest"));
    STR_MESSASSERT(hp[2], std::string("/usr/include/evas-1"));
  }
  void headerParser_testAddHeaderPath()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    m_headerParser->addSearchPath(std::string("/usr/include"));
    m_headerParser->addSearchPath(std::string("/usr/include/evas"));
    std::vector<std::string> hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 4);
    STR_MESSASSERT(hp[0], std::string("/usr/include"));
    STR_MESSASSERT(hp[1], std::string("/usr/include/thisisatest"));
    STR_MESSASSERT(hp[2], std::string("/usr/include/evas-1"));
    STR_MESSASSERT(hp[3], std::string("/usr/include/evas"));
  }
  void headerParser_testAddHeadersPaths()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    std::vector<std::string> input;
    input.push_back(std::string("/usr/include/xcb"));
    input.push_back(std::string("/usr/include/eina"));
    m_headerParser->addSearchPaths(input);
    std::vector<std::string> hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 5);
    STR_MESSASSERT(hp[0], std::string("/usr/include"));
    STR_MESSASSERT(hp[1], std::string("/usr/include/thisisatest"));
    STR_MESSASSERT(hp[2], std::string("/usr/include/evas-1"));
    STR_MESSASSERT(hp[3], std::string("/usr/include/xcb"));
    STR_MESSASSERT(hp[4], std::string("/usr/include/eina"));
  }
  void headerParser_testParse()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    CPPUNIT_ASSERT(m_headerParser->nbStructures() == 6 ); 
  }
  CPPUNIT_TEST_SUITE(TruckBorisSecondConstructorTests);
  CPPUNIT_TEST(headerParser_testInitializedHeaderParser);
  CPPUNIT_TEST(headerParser_testAddHeaderPath);
  CPPUNIT_TEST(headerParser_testAddHeadersPaths);
  CPPUNIT_TEST(headerParser_testParse);
  CPPUNIT_TEST_SUITE_END();
};
class TruckBorisParsingTests: public CppUnit::TestFixture
{
  private:
    TruckBoris::HeaderParser * m_headerParser;
  public:
  void setUp()
  {
    m_headerParser = NULL;
    std::vector<std::string> hp;
    hp.push_back(std::string("/usr/include"));
    m_headerParser = new TruckBoris::HeaderParser(std::string(TEST_SOURCE_FILE),hp);
  }
  void tearDown()
  {
    if(m_headerParser)
    delete m_headerParser;
  }
  void headerParser_testInitializedHeaderParser()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
  }
  void headerParser_testParsingBasic()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    CPPUNIT_ASSERT(m_headerParser->nbStructures() == 6 ); 
    CPPUNIT_ASSERT(m_headerParser->nbEnums() == 3 ); 
    CPPUNIT_ASSERT(m_headerParser->nbFunctions() == 4 ); 
    CPPUNIT_ASSERT(m_headerParser->nbTypedefs() == 7 ); 
    CPPUNIT_ASSERT(m_headerParser->nbUnions() == 1);
  }
  void headerParser_testStructures()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    STR_MESSASSERT(m_headerParser->getStructure(0).getName(), std::string("ana"));
    CPPUNIT_ASSERT(m_headerParser->getStructure(0).hasNameForLinkage() == true);
    CPPUNIT_ASSERT(m_headerParser->getStructure(0).hasLinkage() == true);
    STR_MESSASSERT(m_headerParser->getStructure(0).getTypedefName(), std::string(""));
    CPPUNIT_ASSERT(m_headerParser->getStructure(0).getFields().size() == 1);
    //std::string raw = s[0].getRaw(m_headerParser->getSourceManager(), m_headerParser->getLangOpts());
    //std::string decl("struct ana {\n  int touf;\n} nas;");
    //CPPUNIT_ASSERT_MESSAGE(raw, raw == decl);
    STR_MESSASSERT(m_headerParser->getStructure(1).getName(), std::string("_geronimo"));
    CPPUNIT_ASSERT(m_headerParser->getStructure(1).hasNameForLinkage() == true);
    CPPUNIT_ASSERT(m_headerParser->getStructure(1).hasLinkage() == true);
    STR_MESSASSERT(m_headerParser->getStructure(1).getTypedefName(), std::string(""));
    CPPUNIT_ASSERT(m_headerParser->getStructure(1).getFields().size() == 1);
    STR_MESSASSERT(m_headerParser->getStructure(2).getName(), std::string(""));
    CPPUNIT_ASSERT(m_headerParser->getStructure(2).hasNameForLinkage() == false);
    CPPUNIT_ASSERT(m_headerParser->getStructure(2).hasLinkage() == false);
    STR_MESSASSERT(m_headerParser->getStructure(2).getTypedefName(), std::string(""));
    CPPUNIT_ASSERT(m_headerParser->getStructure(2).getFields().size() == 2);
    STR_MESSASSERT(m_headerParser->getStructure(3).getName(), std::string(""));
    CPPUNIT_ASSERT(m_headerParser->getStructure(3).hasNameForLinkage() == true);
    CPPUNIT_ASSERT(m_headerParser->getStructure(3).hasLinkage() == true);
    STR_MESSASSERT(m_headerParser->getStructure(3).getTypedefName(), std::string("tomate"));
    CPPUNIT_ASSERT(m_headerParser->getStructure(3).getFields().size() == 1);
    STR_MESSASSERT(m_headerParser->getStructure(4).getName(), std::string("_poire"));
    CPPUNIT_ASSERT(m_headerParser->getStructure(4).hasNameForLinkage() == true);
    CPPUNIT_ASSERT(m_headerParser->getStructure(4).hasLinkage() == true);
    STR_MESSASSERT(m_headerParser->getStructure(4).getTypedefName(), std::string(""));
    CPPUNIT_ASSERT(m_headerParser->getStructure(4).getFields().size() == 2);
    STR_MESSASSERT(m_headerParser->getStructure(5).getName(), std::string(""));
    CPPUNIT_ASSERT(m_headerParser->getStructure(5).hasNameForLinkage() == false);
    CPPUNIT_ASSERT(m_headerParser->getStructure(5).hasLinkage() == false);
    STR_MESSASSERT(m_headerParser->getStructure(5).getTypedefName(), std::string(""));
    CPPUNIT_ASSERT(m_headerParser->getStructure(5).getFields().size() == 2);
  }
  void headerParser_testUnions()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    STR_MESSASSERT(m_headerParser->getUnion(0).getName(), std::string("Data"));
    CPPUNIT_ASSERT(m_headerParser->getUnion(0).hasNameForLinkage() == true);
    CPPUNIT_ASSERT(m_headerParser->getUnion(0).hasLinkage() == true);
    STR_MESSASSERT(m_headerParser->getUnion(0).getTypedefName(), std::string(""));
    CPPUNIT_ASSERT(m_headerParser->getUnion(0).getFields().size() == 3);
  }
  void headerParser_testEnums()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    std::vector<TruckBoris::Enum> e;
    e = m_headerParser->getEnums();
    STR_MESSASSERT(e[0].getName(), std::string("strategy"));
    CPPUNIT_ASSERT(e[0].hasNameForLinkage() == true);
    CPPUNIT_ASSERT(e[0].hasLinkage() == true);
    STR_MESSASSERT(e[0].getTypedefName(), std::string(""));
    CPPUNIT_ASSERT(e[0].getConstants().size() == 3);
    STR_MESSASSERT(e[1].getName(), std::string("pipete"));
    CPPUNIT_ASSERT(e[1].hasNameForLinkage() == true);
    CPPUNIT_ASSERT(e[1].hasLinkage() == true);
    STR_MESSASSERT(e[1].getTypedefName(), std::string("")); //aplume
    CPPUNIT_ASSERT(e[1].getConstants().size() == 4);
    STR_MESSASSERT(e[2].getName(), std::string(""));
    CPPUNIT_ASSERT(e[2].hasNameForLinkage() == true);
    CPPUNIT_ASSERT(e[2].hasLinkage() == true);
    STR_MESSASSERT(e[2].getTypedefName(), std::string("baka"));
    CPPUNIT_ASSERT(e[2].getConstants().size() == 3);
  }
  void headerParser_testTypedefs()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    std::vector<TruckBoris::Typedef> t;
    t = m_headerParser->getTypedefs();
    STR_MESSASSERT(t[0].getName(), std::string("toto"));
    STR_MESSASSERT(t[1].getName(), std::string("tomate"));
    STR_MESSASSERT(t[2].getName(), std::string("kudamono"));
    STR_MESSASSERT(t[3].getName(), std::string("equide"));
    STR_MESSASSERT(t[4].getName(), std::string("aplume"));
    STR_MESSASSERT(t[5].getName(), std::string("baka"));
  }
  void headerParser_testFunctions()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    STR_MESSASSERT(m_headerParser->getFunction(0).getName(), std::string("une_fonction"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(0).getParameters().size() == 2);
    CPPUNIT_ASSERT(m_headerParser->getFunction(0).isMain() == false);
    STR_MESSASSERT(m_headerParser->getFunction(1).getName(), std::string("pupute"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(1).getParameters().size() == 2);
    CPPUNIT_ASSERT(m_headerParser->getFunction(1).isMain() == false);
    STR_MESSASSERT(m_headerParser->getFunction(2).getName(), std::string("fonction_vide"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(2).getParameters().size() == 0);
    CPPUNIT_ASSERT(m_headerParser->getFunction(2).isMain() == false);
    STR_MESSASSERT(m_headerParser->getFunction(3).getName(), std::string("main"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(3).getParameters().size() == 2);
    CPPUNIT_ASSERT(m_headerParser->getFunction(3).isMain() == true);
  }
  void headerParser_testParameters()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    STR_MESSASSERT(m_headerParser->getFunction(0).getName(), std::string("une_fonction"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(0).getParameters().size() == 2);
    STR_MESSASSERT(m_headerParser->getFunction(1).getName(), std::string("pupute"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(1).getParameters().size() == 2);
    STR_MESSASSERT(m_headerParser->getFunction(2).getName(), std::string("fonction_vide"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(2).getParameters().size() == 0);
    STR_MESSASSERT(m_headerParser->getFunction(3).getName(), std::string("main"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(3).getParameters().size() == 2);
    std::vector<TruckBoris::Parameter> p;
    p = m_headerParser->getFunction(0).getParameters();
    STR_MESSASSERT(p[0].getName(), std::string("arg1")); 
    STR_MESSASSERT(p[1].getName(), std::string("arg2")); 
    p = m_headerParser->getFunction(1).getParameters(); 
    STR_MESSASSERT(p[0].getName(), std::string("")); 
    STR_MESSASSERT(p[1].getName(), std::string("")); 
    p = m_headerParser->getFunction(3).getParameters();
    STR_MESSASSERT(p[0].getName(), std::string("argc")); 
    STR_MESSASSERT(p[1].getName(), std::string("argv")); 
  }
  void headerParser_testField()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    std::vector<TruckBoris::Field> f;
    f = m_headerParser->getStructure(0).getFields();
    STR_MESSASSERT(f[0].getName(), std::string("touf"));
    f = m_headerParser->getStructure(2).getFields();
    STR_MESSASSERT(f[0].getName(), std::string("titi"));
    STR_MESSASSERT(f[1].getName(), std::string("y"));
    f = m_headerParser->getStructure(3).getFields();
    STR_MESSASSERT(f[0].getName(), std::string("z"));
    f = m_headerParser->getUnion(0).getFields();
    STR_MESSASSERT(f[0].getName(), std::string("i"));
    STR_MESSASSERT(f[1].getName(), std::string("f"));
    STR_MESSASSERT(f[2].getName(), std::string("str"));
  }
  void headerParser_testEnumConstants()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    std::vector<TruckBoris::Enum> e;
    e = m_headerParser->getEnums();
    std::vector<TruckBoris::EnumConstant> c;
    c = e[1].getConstants();
    STR_MESSASSERT(c[0].getName(), std::string("CANON"));
    CPPUNIT_ASSERT(c[0].getValue() == 0); 
    STR_MESSASSERT(c[1].getName(), std::string("FUSIL"));
    CPPUNIT_ASSERT(c[1].getValue() == 3); 
    STR_MESSASSERT(c[2].getName(), std::string("ARC"));
    CPPUNIT_ASSERT(c[2].getValue() == 4); 
    STR_MESSASSERT(c[3].getName(), std::string("CANNEAPECHE"));
    CPPUNIT_ASSERT(c[3].getValue() == 5); 
    c = e[2].getConstants();
    STR_MESSASSERT(c[0].getName(), std::string("POLO"));
    CPPUNIT_ASSERT(c[0].getValue() == 0); 
    STR_MESSASSERT(c[1].getName(), std::string("MARCO"));
    CPPUNIT_ASSERT(c[1].getValue() == 1); 
    STR_MESSASSERT(c[2].getName(), std::string("NADINE"));
    CPPUNIT_ASSERT(c[2].getValue() == 2); 
   
  }
  void headerParser_testType()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    std::vector<TruckBoris::Typedef> t;
    t = m_headerParser->getTypedefs();
    //typedef int toto;
    STR_MESSASSERT(t[0].getType().getName(), std::string("int"));
    CPPUNIT_ASSERT(t[0].getType().isCanonical() == true );  
    //struct _poire {
    //  int g;
    //  tomate rouge;
    //};
    STR_MESSASSERT(t[2].getType().getName(), std::string("struct _poire"));
    STR_MESSASSERT(t[2].getType().getClangTypeClassName(), std::string("Elaborated"));  
    CPPUNIT_ASSERT(t[2].getType().isCanonical() == false ); //ok it is not a canonical QualType 
    STR_MESSASSERT(t[2].getType().getCanonicalType().getName(), std::string("struct _poire"));
    CPPUNIT_ASSERT(t[2].getType().getCanonicalType().isCanonical() == true);
    STR_MESSASSERT(t[2].getType().getCanonicalType().getClangTypeClassName(), std::string("Record"));
    //typedef kudamono tabemono;
    STR_MESSASSERT(t[6].getType().getName(), std::string("kudamono"));
    STR_MESSASSERT(t[6].getType().getClangTypeClassName(), std::string("Typedef"));
    STR_MESSASSERT(t[6].getType().getCanonicalType().getName(), std::string("struct _poire"));
    STR_MESSASSERT(t[6].getType().getCanonicalType().getClangTypeClassName(), std::string("Record"));
    //std::vector<TruckBoris::Structure> s;
    //s = m_headerParser->getStructures();
    std::vector<TruckBoris::Field> f;
    //struct _poire {
    //  int g;
    //  tomate rouge;
    //};
    f = m_headerParser->getStructure(4).getFields();
    STR_MESSASSERT(f[0].getType().getName(), std::string("int"));
    CPPUNIT_ASSERT(f[0].getType().isCanonical() == true);
    STR_MESSASSERT(f[1].getType().getName(), std::string("tomate"));
    CPPUNIT_ASSERT(f[1].getType().isCanonical() == false); //ok it is not a canonical QualType
    STR_MESSASSERT(f[1].getType().getCanonicalType().getName(), std::string("tomate"));
    CPPUNIT_ASSERT(f[1].getType().getCanonicalType().isCanonical() == true);
    //struct {
    //  int zozo;
    //  kudamono fruit;
    //} poney;
    f = m_headerParser->getStructure(5).getFields();
    STR_MESSASSERT(f[0].getType().getName(), std::string("int"));
    CPPUNIT_ASSERT(f[0].getType().isCanonical() == true);
    STR_MESSASSERT(f[1].getType().getName(), std::string("kudamono"));
    CPPUNIT_ASSERT(f[1].getType().isCanonical() == false);
    STR_MESSASSERT(f[1].getType().getCanonicalType().getName(), std::string("struct _poire"));
    std::vector<TruckBoris::Parameter> p;
    p = m_headerParser->getFunction(0).getParameters();
    STR_MESSASSERT(p[0].getType().getName(), std::string("int"));
    CPPUNIT_ASSERT(p[0].getType().isCanonical() == true);
    p = m_headerParser->getFunction(1).getParameters();
    STR_MESSASSERT(p[0].getType().getName(), std::string("tomate *"));
    CPPUNIT_ASSERT(p[0].getType().isCanonical() == false);
    STR_MESSASSERT(p[0].getType().getCanonicalType().getName(), std::string("tomate *"));
    STR_MESSASSERT(p[1].getType().getName(), std::string("const equide *"));
    CPPUNIT_ASSERT(p[1].getType().isCanonical() == false);
    STR_MESSASSERT(p[1].getType().getCanonicalType().getName(), std::string("const struct poney *"));
    //STR_MESSASSERT(p[1].getType().getCanonicalType().getUnqualifiedType().getName(), std::string("nomatch"));
  }
  CPPUNIT_TEST_SUITE(TruckBorisParsingTests);
  CPPUNIT_TEST(headerParser_testInitializedHeaderParser);
  CPPUNIT_TEST(headerParser_testParsingBasic);
  CPPUNIT_TEST(headerParser_testStructures);
  CPPUNIT_TEST(headerParser_testUnions);
  CPPUNIT_TEST(headerParser_testEnums);
  CPPUNIT_TEST(headerParser_testTypedefs);
  CPPUNIT_TEST(headerParser_testFunctions);
  CPPUNIT_TEST(headerParser_testParameters);
  CPPUNIT_TEST(headerParser_testField);
  CPPUNIT_TEST(headerParser_testEnumConstants);
  CPPUNIT_TEST(headerParser_testType);
  CPPUNIT_TEST_SUITE_END();
};
class TruckBorisCppTests: public CppUnit::TestFixture
{
  private:
    TruckBoris::HeaderParser * m_headerParser;
  public:
  void setUp()
  {
    m_headerParser = NULL;
    m_headerParser = new TruckBoris::HeaderParser();
    //m_headerParser->getLangOpts().CPlusPlus = 1;
    clang::CompilerInvocation::setLangDefaults(m_headerParser->getLangOpts(), clang::IK_CXX); 
    m_headerParser->addSourceFile(std::string(TEST_CLASS_SOURCE_FILE));
    m_headerParser->addSearchPath(std::string("/usr/include"));
    m_headerParser->addSearchPath(std::string("/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.1/include"));
  }
  void tearDown()
  {
    if(m_headerParser)
    delete m_headerParser;
  }
  void headerParser_testInitializedHeaderParser()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_CLASS_SOURCE_FILE) );
    std::vector<std::string> hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 2);
    STR_MESSASSERT(hp[0], std::string("/usr/include"));
    STR_MESSASSERT(hp[1], std::string("/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.1/include"));
  }
  void headerParser_testAddHeaderPath()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_CLASS_SOURCE_FILE) );
    m_headerParser->addSearchPath(std::string("/usr/include"));
    m_headerParser->addSearchPath(std::string("/usr/include/evas"));
    std::vector<std::string> hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 3);
    STR_MESSASSERT(hp[0], std::string("/usr/include"));
    STR_MESSASSERT(hp[1], std::string("/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.1/include"));
    STR_MESSASSERT(hp[2], std::string("/usr/include/evas"));
  }
  void headerParser_testAddHeadersPaths()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_CLASS_SOURCE_FILE) );
    std::vector<std::string> input;
    input.push_back(std::string("/usr/include/xcb"));
    input.push_back(std::string("/usr/include/eina"));
    m_headerParser->addSearchPaths(input);
    std::vector<std::string> hp = m_headerParser->getHeadersPaths();
    CPPUNIT_ASSERT(hp.size() == 4);
    STR_MESSASSERT(hp[0], std::string("/usr/include"));
    STR_MESSASSERT(hp[1], std::string("/usr/lib/gcc/x86_64-unknown-linux-gnu/4.9.1/include"));
    STR_MESSASSERT(hp[2], std::string("/usr/include/xcb"));
    STR_MESSASSERT(hp[3], std::string("/usr/include/eina"));
  }
  void headerParser_testParsing()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_CLASS_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    std::vector<TruckBoris::TagDeclaration> classes;
    classes = m_headerParser->getClasses();
    CPPUNIT_ASSERT(classes.size() == 2 ); 
  
  }
  void headerParser_testMethods()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_CLASS_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    CPPUNIT_ASSERT(m_headerParser->nbFunctions() == 2 );
    STR_MESSASSERT(m_headerParser->getFunction(0).getName(), std::string("isTrue"));
  }
  CPPUNIT_TEST_SUITE(TruckBorisCppTests);
  CPPUNIT_TEST(headerParser_testInitializedHeaderParser);
  CPPUNIT_TEST(headerParser_testAddHeaderPath);
  CPPUNIT_TEST(headerParser_testAddHeadersPaths);
  CPPUNIT_TEST(headerParser_testParsing);
  CPPUNIT_TEST(headerParser_testMethods);
  CPPUNIT_TEST_SUITE_END();
};
class TruckBorisScopeParsingTests: public CppUnit::TestFixture
{
  private:
    TruckBoris::HeaderParser * m_headerParser;
  public:
  void setUp()
  {
    m_headerParser = NULL;
    std::vector<std::string> hp;
    hp.push_back(std::string("/usr/include"));
    m_headerParser = new TruckBoris::HeaderParser(std::string(TEST_LIMIT_PARSING_SOURCE_FILE),hp);
  }
  void tearDown()
  {
    if(m_headerParser)
    delete m_headerParser;
  }
  void headerParser_testParsingBasic()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_LIMIT_PARSING_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse() == true);
    CPPUNIT_ASSERT(m_headerParser->nbFunctions() == 4 ); 
    CPPUNIT_ASSERT(m_headerParser->getTypedefs().size() == 8 ); 
  }
  void headerParser_testTypedefs()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_LIMIT_PARSING_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse(false) == true);
    std::vector<TruckBoris::Typedef> t;
    t = m_headerParser->getTypedefs();
    STR_MESSASSERT(t[0].getName(), std::string("toto"));
    STR_MESSASSERT(t[1].getName(), std::string("tomate"));
    STR_MESSASSERT(t[2].getName(), std::string("kudamono"));
    STR_MESSASSERT(t[3].getName(), std::string("equide"));
    STR_MESSASSERT(t[4].getName(), std::string("aplume"));
    STR_MESSASSERT(t[5].getName(), std::string("baka"));
    STR_MESSASSERT(t[6].getName(), std::string("tabemono"));
    STR_MESSASSERT(t[7].getName(), std::string("anInt"));
  }
  void headerParser_testFunctions()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_LIMIT_PARSING_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse(false) == true);
    STR_MESSASSERT(m_headerParser->getFunction(0).getName(), std::string("une_fonction"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(0).getParameters().size() == 2);
    CPPUNIT_ASSERT(m_headerParser->getFunction(0).isMain() == false);
    STR_MESSASSERT(m_headerParser->getFunction(1).getName(), std::string("pupute"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(1).getParameters().size() == 2);
    CPPUNIT_ASSERT(m_headerParser->getFunction(1).isMain() == false);
    STR_MESSASSERT(m_headerParser->getFunction(2).getName(), std::string("tato"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(2).getParameters().size() == 0);
    CPPUNIT_ASSERT(m_headerParser->getFunction(2).isMain() == false);
    STR_MESSASSERT(m_headerParser->getFunction(3).getName(), std::string("main"));
    CPPUNIT_ASSERT(m_headerParser->getFunction(3).getParameters().size() == 2);
    CPPUNIT_ASSERT(m_headerParser->getFunction(3).isMain() == true);
  }
  void headerParser_testMainFileFunctions()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_LIMIT_PARSING_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse(true) == true);
    CPPUNIT_ASSERT(m_headerParser->nbFunctions() == 2 ); 
    //STR_MESSASSERT(m_headerParser->getFunction(0).getName(), std::string("tato"));
    //CPPUNIT_ASSERT(m_headerParser->getFunction(0).getParameters().size() == 0);
    //CPPUNIT_ASSERT(m_headerParser->getFunction(0).isMain() == false);
    //STR_MESSASSERT(m_headerParser->getFunction(1).getName(), std::string("main"));
    //CPPUNIT_ASSERT(m_headerParser->getFunction(1).getParameters().size() == 2);
    //CPPUNIT_ASSERT(m_headerParser->getFunction(1).isMain() == true);
  }
  void headerParser_testMainFileTypedefs()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_LIMIT_PARSING_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse(true) == true);
    std::vector<TruckBoris::Typedef> t;
    t = m_headerParser->getTypedefs();
    STR_MESSASSERT(t[0].getName(), std::string("anInt"));
  }
  void headerParser_testMainFileStructures()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_LIMIT_PARSING_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse(true) == true);
    CPPUNIT_ASSERT(m_headerParser->nbStructures() == 0);
  }
  void headerParser_testMainFileUnions()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_LIMIT_PARSING_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse(true) == true);
    CPPUNIT_ASSERT(m_headerParser->nbUnions() == 0);
  }
  void headerParser_testMainFileEnums()
  {
    CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
    STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_LIMIT_PARSING_SOURCE_FILE) );
    CPPUNIT_ASSERT(m_headerParser->parse(true) == true);
    std::vector<TruckBoris::Enum> e;
    e = m_headerParser->getEnums();
    CPPUNIT_ASSERT(e.size() == 0);
  }
  CPPUNIT_TEST_SUITE(TruckBorisScopeParsingTests);
  CPPUNIT_TEST(headerParser_testParsingBasic);
  CPPUNIT_TEST(headerParser_testTypedefs);
  CPPUNIT_TEST(headerParser_testFunctions);
  CPPUNIT_TEST(headerParser_testMainFileFunctions);
  CPPUNIT_TEST(headerParser_testMainFileTypedefs);
  CPPUNIT_TEST(headerParser_testMainFileStructures);
  CPPUNIT_TEST(headerParser_testMainFileUnions);
  CPPUNIT_TEST(headerParser_testMainFileEnums);
  CPPUNIT_TEST_SUITE_END();
};
#endif
