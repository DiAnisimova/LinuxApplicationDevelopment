prog: const.o fun.o prog.o
	cc const.o fun.o prog.o -o prog

prog-a: prog.o liboutput_static.a
	cc -L. prog.o -static -loutput_static -o prog-a

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o prog-so

liboutput_static.a: const.o fun.o
	ar -rcs liboutput_static.a fun.o const.o

liboutput.so: const.o fun.o
	cc -shared const.o fun.o -o liboutput.so

fun.o: fun.c 
	cc fun.c -c -fPIC -o fun.o

prog.o: prog.c
	cc prog.c -c -fPIC -o prog.o

const.o: const.c 
	cc const.c -c -fPIC -o const.o

test: prog prog-a prog-so
	./prog > test_null.txt 2>&1
	./prog-a > test_a_null.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > test_so_null.txt 2>&1
	./prog KVA > test_one.txt 2>&1
	./prog-a KVA > test_a_one.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so KVA > test_so_one.txt 2>&1
	./prog ha haha hahaha > test_three.txt 2>&1
	./prog-a ha haha hahaha > test_a_three.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so ha haha hahaha > test_so_three.txt 2>&1
	cmp test_null.txt test_a_null.txt
	cmp test_null.txt test_so_null.txt
	cmp test_one.txt test_a_one.txt
	cmp test_one.txt test_so_one.txt
	cmp test_three.txt test_a_three.txt
	cmp test_three.txt test_so_three.txt


clean:
	rm -f prog prog-a prog-so a.out *.o *.txt *.so *.a
