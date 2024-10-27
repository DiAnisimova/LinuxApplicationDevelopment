#!/bin/bash

echo "This is a test file." > infile.txt

./move infile.txt outfile.txt
if [ $? -ne 0 ]; then
    echo "Test failed: move should succeed."
    exit 1
fi

if [ -f "infile.txt" ] || [ ! -f "outfile.txt" ]; then
    echo "Test failed: infile.txt should be deleted, outfile.txt should exist."
    exit 1
fi

echo "Test 1 passed: Successful move."

echo "This is a test file." > infile.txt

strace -e file --fault=openat:error=ENOENT:when=3 ./move infile.txt outfile.txt 2>/dev/null
if [ $? -ne 2 ]; then
    echo "Test failed: Should return exit code 2 when infile cannot be opened."
    exit 1
fi

echo "Test 2 passed: Error opening infile."

strace -e file --fault=openat:error=ENOENT:when=4 ./move infile.txt outfile.txt 2>/dev/null
if [ $? -ne 3 ]; then
    echo "Test failed: Should return exit code 3 when outfile cannot be opened."
    exit 1
fi

echo "Test 3 passed: Error opening outfile."

strace -e desc --fault=read:error=EIO:when=2 ./move infile.txt outfile.txt 2>/dev/null
if [ $? -ne 4 ]; then
    echo "Test failed: Should return exit code 4 when infile can't be read."
    exit 1
fi

echo "Test 4 passed: Error reading from infile."

strace -e desc --fault=write:error=EIO:when=1 ./move infile.txt outfile.txt 2>/dev/null
if [ $? -ne 5 ]; then
    echo "Test failed: Should return exit code 5 when outfile cannot be written into."
    exit 1
fi

echo "Test 5 passed: Error writing to outfile."

strace -e desc --fault=close:error=ENOSPC:when=3 ./move infile.txt outfile.txt 2>/dev/null
if [ $? -ne 6 ]; then
    echo "Test failed: Should return exit code 6 when infile cannot be closed."
    exit 1
fi

echo "Test 6 passed: Error closing infile."

strace -e desc --fault=close:error=ENOSPC:when=4 ./move infile.txt outfile.txt 2>/dev/null
if [ $? -ne 7 ]; then
    echo "Test failed: Should return exit code 7 when outfile cannot be closed."
    exit 1
fi

echo "Test 7 passed: Error closing outfile."

strace -e file --fault=unlink:error=EPERM ./move infile.txt outfile.txt 2>/dev/null
if [ $? -ne 8 ]; then
    echo "Test failed: Should return exit code 8 when infile cannot be deleted."
    exit 1
fi

echo "Test 8 passed: Error deleting infile."

echo "This is a test file with special protection." > PROTECT_infile.txt

LD_PRELOAD=./overload_remove.so ./move PROTECT_infile.txt outfile.txt 2>/dev/null
if [ $? -ne 8 ] || [ ! -f "PROTECT_infile.txt" ] || [ ! -f "outfile.txt" ]; then
    echo "Test failed: Should copy correctly, but be unable to delete the infile"
    exit 1
fi

echo "Test 9 passed: Overloading remove() with LD_PRELOAD"

echo "This is a test file." > infile.txt
cat PROTECT_infile.txt > PROTECT_outfile.txt

LD_PRELOAD=./overload_remove.so strace -e file ./move infile.txt PROTECT_outfile.txt 2>/dev/null
if [ $? -ne 3 ] || [ ! -f "infile.txt" ] || [ ! -f "PROTECT_outfile.txt" ] || "cmp" "-s" "PROTECT_infile.txt" "PROTECT_OUTFILE.txt"; then
    echo "Test failed: Should fail to open the outfile"
    exit 1
fi

echo "Test 10 passed: Overloading fopen() with LD_PRELOAD"

# Clean up
rm -f infile.txt PROTECT_infile.txt outfile.txt PROTECT_outfile.txt

echo "All tests passed."
