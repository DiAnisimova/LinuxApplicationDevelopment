AC_PREREQ([2.69])
AC_INIT([Guess guess], [1.0], [diana.anisimova.01@mail.ru], [guess])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([guess])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.19])
AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])
AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")
ALL_LINGUAS="ru"

AC_PROG_CC
IT_PROG_INTLTOOL

PKG_CHECK_MODULES([CHECK], [check])
AC_SUBST(CK_VERBOSITY, verbose)
AC_ARG_VAR(CK_VERBOSITY, [Default: "verbose", can be "silent", "minimal" or "normal"])

AC_ARG_ENABLE([gcov],
              [AS_HELP_STRING([--enable-gcov], [use Gcov to test the test suite])],
              [], [enable_gcov=no])
AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h guess.h])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    po/Makefile.in
    tests/Makefile
    Doxyfile
])
AC_OUTPUT
