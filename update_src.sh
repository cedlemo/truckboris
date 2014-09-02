#!/usr/bin/bash
source_files=("Declarations.cpp" "Function.cpp" "HeaderElements.cpp" "HeaderParser.cpp"
 "Type.cpp" "dbg.h" "gears.cpp" "parser.cpp" "Declarations.h" "Function.h" "HeaderElements.h"
 "HeaderParser.h" "Type.h" "gears.h")

for i in "${source_files[@]}"; do
  vimdiff ~/projets/C++/Clang/TruckBoris-Ruby-Swig/ext/parser/$i ./$i
  echo $i
done
