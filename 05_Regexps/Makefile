esub: esub.c
	gcc esub.c -o esub

test: esub
	./esub > esub_test_1.txt
	echo | sed -E '' > sed_test_1.txt
	./esub "ab" "a\1b" "ab" > esub_test_2.txt
	#echo 'ab' | sed -E 's/ab/a\1b/' > sed_test_2.txt
	./esub "a(b" "ab" "ab" > esub_test_3.txt
	#echo 'ab' | sed -E 's/a(b/ab/' > sed_test_3.txt
	./esub "ab" "BA" "eabc" > esub_test_4.txt
	echo "eabc" | sed -E 's/ab/BA/' > sed_test_4.txt
	./esub "a(b)c" "\1_\1" "DabcE" > esub_test_5.txt
	echo 'DabcE' | sed -E 's/a(b)c/\1_\1/' > sed_test_5.txt
	./esub "(a)b(c)d(e)" "<\3\2\1>" "_abcdef_" > esub_test_6.txt
	echo '_abcdef_' | sed -E 's/(a)b(c)d(e)/<\3\2\1>/' > sed_test_6.txt
	./esub "([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)" "\4, \2 \3 year of \1" "2024 17 October Thursday" > esub_test_7.txt
	echo '2024 17 October Thursday' | sed -E 's/([[:digit:]]{4}) +([[:digit:]]{1,2}) +([[:alpha:]]+) +([[:alpha:]]+)/\4, \2 \3 year of \1/' > sed_test_7.txt
	#cmp esub_test_1.txt sed_test_1.txt
	#cmp esub_test_2.txt sed_test_2.txt
	#cmp esub_test_3.txt sed_test_3.txt
	cmp esub_test_4.txt sed_test_4.txt
	cmp esub_test_5.txt sed_test_5.txt
	cmp esub_test_6.txt sed_test_6.txt
	cmp esub_test_7.txt sed_test_7.txt

clean:
	rm -f esub *.txt
