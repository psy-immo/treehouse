#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([termTrees], [0.1], [immo@zorgk.de])
AC_CONFIG_SRCDIR([src/termTrees.c])
AC_CONFIG_HEADERS([config.h]) 

# Checks for programs.
AC_PROG_CC


# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([limits.h stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([memmove memset])

AM_INIT_AUTOMAKE(termTrees, 0.1)
AC_OUTPUT(Makefile src/Makefile)
