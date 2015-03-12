AC_PREREQ(2.69)
AC_INIT(truckBoris, 1.0.2, cedlemo@gmx.fr)
AC_CONFIG_SRCDIR(configure.ac)
AM_CONFIG_HEADER(config.h)
AC_SUBST([LLVMCONFIG],[$(which llvm-config)])
AC_SUBST([LLVMLDFLAGS],[$($LLVMCONFIG --ldflags )])
AC_SUBST([LLVMLIBS],[$($LLVMCONFIG --libs )])
AC_SUBST([LLVMCXXFLAGS],[$($LLVMCONFIG --cxxflags)])
AC_SUBST([LLVMSYSLIBS],[$($LLVMCONFIG --system-libs )])
AC_PROG_CC(clang gcc)
AC_PROG_CXX(clang++ g++)
m4_include([m4/unique_ptr.m4])
AM_INIT_AUTOMAKE(1.13 dist-bzip2 foreign subdir-objects)
AM_PATH_CPPUNIT(1.12.1)
LT_PREREQ(2.4)
LT_INIT
AX_CXX_TYPE_UNIQUE_PTR
AC_CONFIG_FILES([
  Makefile
  truckboris.pc
])
AC_OUTPUT
