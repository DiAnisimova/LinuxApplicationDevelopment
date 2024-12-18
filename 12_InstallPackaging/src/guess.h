#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define _(STRING) gettext(STRING)

/** @file guess.h
*/

/** Converts a string into an integer
 * @param str The numeral string
 * @param out The result number
 * @return The integer value - success of operation 
 */

int safe_atoi(const char *str, int *out) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    const char *ptr = str;
    if (*ptr == '+' || *ptr == '-') {
        ptr++;
    }
    while (*ptr) {
        if (!isdigit(*ptr)) {
            return 0;
        }
        ptr++;
    }
    errno = 0;
    long result = strtol(str, NULL, 10);
    if ((result > INT_MAX || result < INT_MIN) || errno == ERANGE) {
        return 0;
    }
    *out = (int)result;
    return 1;
}

/** Function to print help message.
 */
void print_help() {
    printf(_("Usage: ./program_name <NUMBER or OPTIONS>\n"));
    printf(_("Options:\n"));
    printf(_("\t--help\tDisplay this help message and exit.\n"));
}

/** Tries to determine whether a number is even or not.
*/
char *odd_or_even(int n) {
    if (n % 2 == 0) {
	return _("It is an even number.\n");
    }
    
    if (n % 2 != 0) {
	return _("It is an odd number.\n");
    }
}
