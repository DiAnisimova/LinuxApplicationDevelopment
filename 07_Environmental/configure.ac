AC_INIT([rhasher], [1.0], [diana.anisimova.01@mail.ru])
AM_INIT_AUTOMAKE([foreign])
AC_PROG_CC
AC_CHECK_LIB([rhash], [rhash_init], [], [AC_MSG_ERROR([RHash library not found!])])

AC_ARG_ENABLE([readline],
  [AS_HELP_STRING([--disable-readline],
   [do not compile with readline support])],
  [readline_enabled=$enableval], [readline_enabled=yes])

if test "x$readline_enabled" = "xyes"; then
  AC_CHECK_LIB([readline], [readline],
    [readline_lib="-lreadline"; AC_DEFINE([USE_READLINE], [1], [Using Readline])],
    [AC_MSG_WARN([Readline library not found, proceeding without it]);])
else
  readline_lib=""
fi

AC_SUBST(readline_lib)
AM_CONDITIONAL([USE_READLINE], [test "x$readline_lib" = "x-lreadline"])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
