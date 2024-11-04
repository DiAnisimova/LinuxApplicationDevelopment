#!/bin/sh

set -e

aclocal
autoconf
automake --add-missing
./configure
make
make check
make clean
./configure --disable-readline
make
make check
make clean
make distclean
