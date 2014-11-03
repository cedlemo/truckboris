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
