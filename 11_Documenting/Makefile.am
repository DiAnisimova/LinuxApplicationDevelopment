@DX_RULES@

all-local:  doxygen-doc

SUBDIRS = src po

clean:
	rm -rf ABOUT-NLS aclocal.m4 autom4te.cache ChangeLog compile config.* configure configure~ depcomp install-sh m4 Makefile Makefile.in missing stamp-h1 po/boldquot.sed po/ChangeLog po/en@* po/insert-header.sin po/Makefile po/Makefile.in* po/Makevars.template po/POTFILES po/quot.sed po/remove-potcdate.sin po/Rules-quot src/.deps/ src/guess src/guess.o src/Makefile src/Makefile.in po/ru po/ru.gmo po/stamp-it Doxyfile doxygen-doc/ latex/ man/ html/

http: doxygen-doc
	python3 -m http.server --directory $</html
