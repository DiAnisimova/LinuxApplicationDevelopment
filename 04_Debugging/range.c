#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    long n = 0;
    long m = 0;
    long s = 1;
    if (argc == 1) {
	printf("help\n");
    } else if (argc == 2) {
	n = strtol(argv[1], NULL, 10);
	for (long i = 0; i < n; i++) {
	    printf("%ld\n", i);
	}
    } else {
	m = strtol(argv[1], NULL, 10);
	n = strtol(argv[2], NULL, 10);
	if (argc == 4) {
	    s = strtol(argv[3], NULL, 10);
	}
	for (long i = m; i < n; i += s) {
	    printf("%ld\n", i);
	}
    }
    return 0;
}
