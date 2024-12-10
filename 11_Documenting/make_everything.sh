#!/bin/sh

set -e

autoreconf -fisv
./configure
make AM_CFLAGS=-D'LOCALEDIR=\"po\"' all
install -D po/ru.gmo po/ru/LC_MESSAGES/guess.mo
make http
