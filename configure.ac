AC_INIT(TruckBorisTests, 0.0.0, cedlemo@gmx.fr)
AC_PREREQ(2.52)
AC_CONFIG_SRCDIR(configure.ac)
AM_CONFIG_HEADER(config.h)
AC_SUBST([LLVMCONFIG],[$(which llvm-config)])
AC_SUBST([LLVMLDFLAGS],[$($LLVMCONFIG --ldflags )])
AC_SUBST([LLVMLIBS],[$(llvm-config --libs )])
AC_PROG_CXX
AC_PROG_CC
AM_INIT_AUTOMAKE(1.6 dist-bzip2)
AM_PATH_CPPUNIT(1.13.2)
AC_OUTPUT(Makefile)
