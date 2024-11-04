#!/bin/sh

echo -n 'MD5 "Test string"' > test.txt
expected=$(echo -n "Test string" | md5sum | awk '{ print $1 }')
result=$(./rhasher < test.txt)

if [ "$result" = "$expected" ]; then
  echo "MD5 test passed."
else
  echo "MD5 test failed: Expected $expected, got $result"
  exit 1
fi

rm -f test.txt
