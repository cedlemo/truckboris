AC_PREREQ(2.68)
AC_INIT(truckBoris, 1.0.3, cedlemo@gmx.fr)
AC_CONFIG_SRCDIR(configure.ac)
AM_CONFIG_HEADER(config.h)
AC_SUBST([LLVMCONFIG],[$(which llvm-config)])
AC_SUBST([LLVMLDFLAGS],[$($LLVMCONFIG --ldflags )])
AC_SUBST([LLVMLIBS],[$($LLVMCONFIG --libs )])
clang_major=$(find /usr/include/ -type f | xargs grep "#define CLANG_VERSION_MAJOR"|rev|cut -d" " -f1)
clang_minor=$(find /usr/include/ -type f | xargs grep "#define CLANG_VERSION_MINOR"|rev|cut -d" " -f1)
llvm_major=$(find /usr/include/ -type f | xargs grep "#define LLVM_VERSION_MAJOR"|head -1|rev|cut -d" " -f1)
llvm_minor=$(find /usr/include/ -type f | xargs grep "#define LLVM_VERSION_MINOR"|head -1|rev|cut -d" " -f1)
if [[ $clang_major -eq "3" ]];then
  #then echo "############################################3"
  #Clang 3.4 doesn't support -fstack-protector-strong option
  if [[ $clang_minor -eq "4" ]];then
    #then echo "############################################4"
    AC_SUBST([LLVMCXXFLAGS],[$($LLVMCONFIG --cxxflags | /usr/bin/sed 's/ -fstack-protector-strong//g')])
  else
    AC_SUBST([LLVMCXXFLAGS],[$($LLVMCONFIG --cxxflags)])
  fi
fi
if [[ $llvm_major -eq "3" ]]; then
  #llvm-config 3.4 doesn't support --system-libs option
  if [[ $llvm_minor -eq "4" ]]; then
    AC_SUBST([LLVMSYSLIBS],[""])
  else
    AC_SUBST([LLVMSYSLIBS],[$($LLVMCONFIG --system-libs )])
  fi
fi
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
