CXX = clang++
AUTOMAKE_OPTIONS = 1.4 foreign
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure depcomp install-sh missing compile
#RTTIFLAG = #-fno-rtti
CLANGCXXFLAGS := -I$(shell @LLVMCONFIG@ --src-root)/tools/clang/include \
                -I$(shell @LLVMCONFIG@ --obj-root)/tools/clang/include \
                $(shell @LLVMCONFIG@ --cxxflags) -fcxx-exceptions
CLANGLIBS = -lclangTooling\
        -lclangFrontendTool\
        -lclangFrontend\
        -lclangDriver\
        -lclangSerialization\
        -lclangCodeGen\
        -lclangParse\
        -lclangSema\
        -lclangStaticAnalyzerFrontend\
        -lclangStaticAnalyzerCheckers\
        -lclangStaticAnalyzerCore\
        -lclangAnalysis\
        -lclangARCMigrate\
        -lclangRewriteFrontend\
        -lclangRewriteCore\
        -lclangEdit\
        -lclangAST\
        -lclangLex\
        -lclangBasic\
                -lcurses
TEST= truckBorisTests
check_PROGRAMS = $(TEST) 
# TODO set the files sources and test this shit
truckBorisTests_SOURCES = Declarations.cpp  Function.cpp  HeaderElements.cpp  HeaderParser.cpp  TruckBorisTest.cpp  Type.cpp  gears.cpp 
truckBorisTests_CXXFLAGS = $(CPPUNIT_FLAGS) $(CLANGCXXFLAGS) 
truckBorisTests_LDFLAGS = $(CPPUNIT_LIBS) -ldl @LLVMLDFLAGS@ 
truckBorisTests_LDADD = $(CLANGLIBS) @LLVMLIBS@ 
