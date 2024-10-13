range: range.c
	gcc -O0 -g range.c -o range

test: range
	gdb --batch --q -x scen1.gdb --args ./range 1 12 > output1.txt
	gdb --batch --q -x scen2.gdb --args ./range -100 100 3 > output2.txt
	grep @@@ output1.txt > filtered_output1.txt
	grep @@@ output2.txt > filtered_output2.txt
	cmp filtered_output1.txt reference1.txt
	cmp filtered_output2.txt reference2.txt

clean:
	rm -f range *out*.txt
