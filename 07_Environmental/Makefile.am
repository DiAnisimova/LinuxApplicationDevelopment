bin_PROGRAMS = rhasher
rhasher_SOURCES = rhasher.c
rhasher_LDADD = -lrhash $(readline_lib)

# Define test scripts
TESTS = tests/md5_test.sh tests/sha1_test.sh
EXTRA_DIST = $(TESTS)

distclean-local:
	rm -rf .deps aclocal.m4 autom4te.cache/ compile config.log config.status configure depcomp install-sh Makefile Makefile.in missing rhasher rhasher.o test-driver
