# Truckboris

[![Build Status](https://travis-ci.org/cedlemo/truckboris.svg?branch=master)](https://travis-ci.org/cedlemo/truckboris)

Truckboris is a little library based on Clang. Truckboris allows you to easily 
create a simple C source file parser. 

```c++
#include <string>
#include <iostream>
#include <vector>
#include <HeaderParser.h>

#define TEST_SOURCE_FILE "../data/test.cpp"
/*Compile with:
clang++ -o libtest_headerParser_obj $(pkg-config --libs --cflags truckboris) libtest_headerParser_obj.cpp
*/
int main(int argc, char **argv)
{
  std::vector<std::string> hp;
  hp.push_back(std::string("/usr/include"));
  TruckBoris::HeaderParser headerParser;
  headerParser.addSourceFile(std::string(TEST_SOURCE_FILE));
  headerParser.addSearchPaths(hp);

  if(headerParser.isInitialized())
    std::cout << "Header Parser is initialized " << std::endl;
  else
    return 1;
  std::cout << "File to parse : " << headerParser.getSourceFile() << std::endl;

  if(headerParser.parse())
    std::cout << "Parsing succeeded " << std::endl;
  else
    std::cout << "Parsing failed " << std::endl;

  std::vector<TruckBoris::Function> fns;
  fns = headerParser.getFunctions();
  std::cout << fns.size() << std::endl;
  return 0;
}
```

The <code>TruckBoris::HeaderParser</code> object, lists all top level functions , typedefs,
structures, unions enumerations. When the parsing is done you can get, from  
each functions for example, its name, its return type or an array of arguments.

You can see in the file tests/TruckBorisTests.h how to use all the TruckBoris objects
and methodsi with the source files in data/.

```c++
void setUp()
{
  m_headerParser = NULL;
  std::vector<std::string> hp;
  hp.push_back(std::string("/usr/include"));
  m_headerParser = new TruckBoris::HeaderParser(std::string(TEST_SOURCE_FILE),hp);
}
/*-------------------------------*/
void headerParser_testFunctions()
{
  CPPUNIT_ASSERT(m_headerParser->isInitialized() == true);
  STR_MESSASSERT(m_headerParser->getSourceFile(), std::string(TEST_SOURCE_FILE) );
  CPPUNIT_ASSERT(m_headerParser->parse() == true);
  std::vector<TruckBoris::Function> f;
  f = m_headerParser->getFunctions();
  STR_MESSASSERT(f[0].getName(), std::string("une_fonction"));
  CPPUNIT_ASSERT(f[0].getParameters().size() == 2);
  CPPUNIT_ASSERT(f[0].isMain() == false);
  STR_MESSASSERT(f[1].getName(), std::string("pupute"));
  CPPUNIT_ASSERT(f[1].getParameters().size() == 2);
  CPPUNIT_ASSERT(f[1].isMain() == false);
  STR_MESSASSERT(f[2].getName(), std::string("fonction_vide"));
  CPPUNIT_ASSERT(f[2].getParameters().size() == 0);
  CPPUNIT_ASSERT(f[2].isMain() == false);
  STR_MESSASSERT(f[3].getName(), std::string("main"));
  CPPUNIT_ASSERT(f[3].getParameters().size() == 2);
  CPPUNIT_ASSERT(f[3].isMain() == true);
}
```

## Dependencies

TruckBoris depends on LLVM and Clang >= 3.4. You need CPPUNIT (>= 1.12) for the tests.

## Installation

### Systems tested : 
*    Archlinux (clang 3.6, CppUnit 1.13)
*    Fedora    (clang 3.5, CppUnit 1.12)
*    Centos    (clang 3.4, CppUnit 1.12)

### Get the repository:
<code>git clone https://github.com/cedlemo/truckboris</code>

### Generate the make file and install

    ./autogen.sh --prefix=/usr #use the prefix you want
    make 
    sudo make install

With this configuration, the installation create those files/directory:
*    /usr/lib/libtruckboris.{so,la,so.1,so.x.x.x}
*    /usr/include/truckboris with the needed headers.
*    /usr/include/pkgconfig/truckboris.pc

## Use truckboris:
For example, with the file tests/libtest_headerParser_obj.cpp:

<code>clang++ -o libtest_headerParser_obj $(pkg-config --libs --cflags truckboris) libtest_headerParser_obj.cpp</code>

You don't have to bother with the clang LLVM flags.
