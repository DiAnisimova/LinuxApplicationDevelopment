AC_PREREQ([2.69])
AC_INIT([guess], [1.0], [diana.anisimova.01@mail.ru])
AM_INIT_AUTOMAKE([foreign])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.19])
AC_CONFIG_SRCDIR([src/guess.c])
AC_CONFIG_HEADERS([config.h])
AC_SUBST(GETTEXT_PACKAGE, "$PACKAGE")
ALL_LINGUAS="ru"

AC_PROG_CC
IT_PROG_INTLTOOL

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    po/Makefile.in
])
AC_OUTPUT
