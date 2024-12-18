#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "guess.h"

#define _(STRING) gettext(STRING)

/** @mainpage Guess My Number Game

    This program is a simple number guessing game. The user thinks of an integer number,
    and the program tries to determine whether a number is even or not.

    The program supports multiple languages via gettext.

    Usage:
    \code{.unparsed}
    guess [--help]
    \endcode

    Options:
    - -h, --help: Display this help message.

*/


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALEDIR);
    textdomain("guess");

    if (argc < 2) {
	fprintf(stderr, _("Not enough command line arguments.\n"));
	return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "--help") == 0) {
        print_help();
        return EXIT_SUCCESS;
    }

    int n;
    int res = safe_atoi(argv[1], &n);
    if (res == 0) {
	fprintf(stderr, _("Incorrect number format.\n"));
	return EXIT_FAILURE;
    }
    
    char *verdict = odd_or_even(n);
    printf(verdict);
    return EXIT_SUCCESS;
}
