#ifndef GEARS_H
#define GEARS_H

#include "clang/Frontend/CompilerInstance.h"
#include <vector>
#include <string>
void displayUsage(char * progName, const char * error);
void parseArgs(int argc, char **argv, std::vector<std::string>& sourceFiles, std::vector<std::string>& searchPaths);
void initializeCompilerInstance(clang::CompilerInstance& ci, const std::vector<std::string>& searchPaths);
bool loadSourceFile(clang::CompilerInstance& ci, const std::string& name);
#endif
