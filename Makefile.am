CXX = clang++
MAINTAINERCLEANFILES = \
Makefile.in aclocal.m4 config.h.in configure \
depcomp install-sh missing compile config.sub \
config.guess ltmain.sh

CLANGCXXFLAGS := -I$(shell @LLVMCONFIG@ --src-root)/tools/clang/include \
                -I$(shell @LLVMCONFIG@ --obj-root)/tools/clang/include \
                @LLVMCXXFLAGS@ -fcxx-exceptions
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
        -lclangEdit\
        -lclangAST\
        -lclangLex\
        -lclangBasic\
        @LLVMSYSLIBS@
TEST= tests/truckBorisTests
check_PROGRAMS = $(TEST) 
tests_truckBorisTests_SOURCES = src/Declarations.cpp  src/Function.cpp  src/HeaderElements.cpp  src/HeaderParser.cpp  tests/TruckBorisTest.cpp  src/Type.cpp 
tests_truckBorisTests_CXXFLAGS = $(CPPUNIT_FLAGS) $(CLANGCXXFLAGS) 
tests_truckBorisTests_LDFLAGS = $(CPPUNIT_LIBS) -ldl @LLVMLDFLAGS@ 
tests_truckBorisTests_LDADD = $(CLANGLIBS) @LLVMLIBS@

lib_LTLIBRARIES = src/libtruckboris.la
src_libtruckboris_la_SOURCES = src/Declarations.cpp src/Function.cpp src/HeaderElements.cpp src/HeaderParser.cpp src/Type.cpp
src_libtruckboris_la_CXXFLAGS = $(CPPUNIT_FLAGS) $(CLANGCXXFLAGS) 
src_libtruckboris_la_LDFLAGS = $(CPPUNIT_LIBS) -ldl @LLVMLDFLAGS@ -shared -version-info 1:0:0
src_libtruckboris_la_LIBADD = $(CLANGLIBS) @LLVMLIBS@

pkginclude_HEADERS = src/Declarations.h  src/Function.h  src/HeaderElements.h  src/HeaderParser.h  src/Type.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = truckboris.pc

