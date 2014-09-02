require 'mkmf'
CONFIG['CXX']='clang++'
clangLibs = [
"clangFrontend",
"clangDriver",
"clangSerialization",
#"clangTooling",
"clangParse",
"clangSema",
#"clangRewrite",
"clangAnalysis",
"clangEdit",
#"clangASTMatchers",
#"clangFormat",
#"clangCodeGen",
#"clangConfig",
#"clangARCMigrate",
"clangAST",
"clangLex",
"clangBasic"
#"clangIndex",
#"clangFrontendTool",
#"clangStaticAnalyzer",
]
clangLibs.reverse_each do |lib|
  have_library(lib)
end
#Dir.glob("/usr/include/clang/*") .each do |dir|
#  have_library("clang#{File.basename(dir)}")
#end
#$CPPFLAGS = ""
#$CPPFLAGS += ' ' + `llvm-config --cxxflags`.chomp
#$CPPFLAGS += " -fno-rtti"
#puts $LDFLAGS
#$LDFLAGS = `llvm-config --libs`.chomp 
$LDFLAGS += " " + `llvm-config --ldflags`.chomp
#$LDFLAGS += " cppbackend"
#if $CXXFLAGS
#  $CXXFLAGS += `llvm-config --cxxflags`
#else
#  $CXXFLAGS = `llvm-config --cxxflags`
#end
#$LIBS += " " + `llvm-config --libs cppbackend`.chomp
$LIBS += " " + `llvm-config --libs`.chomp
#$LIBS += `llvm-config --ldflags`.chomp
$CPPFLAGS += " -I" + `llvm-config --src-root`.chomp + "/tools/clang/include"
$CPPFLAGS += " -I" + `llvm-config --obj-root`.chomp + "/tools/clang/include"
$CPPFLAGS += " " + `llvm-config --cxxflags`.chomp
$CPPFLAGS += " -fno-rtti"
#$CPPFLAGS += " -fcxx-exceptions"
create_makefile('parser/parser')
