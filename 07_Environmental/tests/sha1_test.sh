#!/bin/sh

echo -n 'SHA1 "Test string"' > test.txt
expected=$(echo -n "Test string" | sha1sum | awk '{ print $1 }')
result=$(./rhasher < test.txt)

if [ "$result" = "$expected" ]; then
  echo "SHA1 test passed."
else
  echo "SHA1 test failed: Expected $expected, got $result"
  exit 1
fi

rm -f test.txt
