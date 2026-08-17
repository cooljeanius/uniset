dnl#                                               -*- Autoconf -*-
dnl# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT([uniset],[0.1],[depp@zdome.net])
AM_INIT_AUTOMAKE([1.5 foreign subdir-objects nostdinc])
AC_CONFIG_SRCDIR([src/token.h])

# Checks for programs.
AC_PROG_CC dnl# specifying "_99" specifically is obsolete now
ENABLE_WARNINGS

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdint.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_C_RESTRICT
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([munmap strdup])

# Output.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
