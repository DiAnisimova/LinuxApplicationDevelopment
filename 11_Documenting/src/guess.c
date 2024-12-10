#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <stdbool.h>

#define _(STRING) gettext(STRING)

/** @mainpage Guess My Number Game

    This program is a simple number guessing game. The user thinks of a number between 1 and 100,
    and the program tries to guess it by asking a series of questions.

    The program supports two modes:
    - **Standard mode**: Uses Arabic numerals.
    - **Roman numeral mode**: Uses Roman numerals (support for numbers between I and C).

    The program also supports multiple languages via gettext.

    Usage:
    \code{.unparsed}
    guess [-r] [--help]
    \endcode

    Options:
    - -r, --roman: Use Roman numerals.
    - -h, --help: Display this help message.

*/

/** Converts an integer to a Roman numeral string.
 * @param num The integer to convert (1..100)
 * @param roman The buffer to store the Roman numeral string (assumed large enough)
 */
void integerToRoman(int num, char *roman) {
    struct {
        int value;
        const char *symbol;
    } romanMappings[] = {
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };

    roman[0] = '\0';
    for (int i = 0; i < 9; i++) {
        while (num >= romanMappings[i].value) {
            strcat(roman, romanMappings[i].symbol);
            num -= romanMappings[i].value;
        }
    }
}

/** Converts a Roman numeral string into an integer.
 * @param roman The Roman numeral string
 * @return The integer value
 */
int romanToInteger(const char *roman) {
    struct {
        const char *symbol;
        int value;
    } romanMappings[] = {
        {"C", 100}, {"XC", 90}, {"L", 50}, {"XL", 40},
        {"X", 10}, {"IX", 9}, {"V", 5}, {"IV", 4}, {"I", 1}
    };

    int num = 0;
    while (*roman) {
        for (int i = 0; i < 9; i++) {
            size_t len = strlen(romanMappings[i].symbol);
            if (strncmp(roman, romanMappings[i].symbol, len) == 0) {
                num += romanMappings[i].value;
                roman += len;
                break;
            }
        }
    }
    return num;
}

/** Function to print help message.
 */
void print_help() {
    printf(_("Usage: ./program_name [OPTION]\n"));
    printf(_("Options:\n"));
    printf(_("\t-r\tPlay the game using Roman numerals instead of numbers.\n"));
    printf(_("\t--help\tDisplay this help message and exit.\n"));
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALEDIR);
    textdomain("guess");

    bool useRoman = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) {
            useRoman = true;
        } else if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return EXIT_SUCCESS;
        }
    }

    int low = 1;
    int high = 100;
    int guess;
    char answer[16384];

    printf(_("Think of a number between 1 and 100.\n"));

    while (low <= high) {
        guess = (low + high) / 2;
        if (useRoman) {
            char romanGuess[16];
            integerToRoman(guess, romanGuess);
            printf(_("Is your number greater than %s? (yes/no): "), romanGuess);
        } else {
            printf(_("Is your number greater than %d? (yes/no): "), guess);
        }

        if (scanf("%s", answer) != 1) {
            fprintf(stderr, _("Error reading input.\n"));
            return EXIT_FAILURE;
        }

        if (strcmp(answer, _("yes")) == 0) {
            low = guess + 1;
        } else if (strcmp(answer, _("no")) == 0) {
            high = guess;
        } else {
            printf(_("Please answer 'yes' or 'no'.\n"));
        }

        if (low == high) {
            if (useRoman) {
                char romanLow[16];
                integerToRoman(low, romanLow);
                printf(_("Your number is %s!\n"), romanLow);
            } else {
                printf(_("Your number is %d!\n"), low);
            }
            break;
        }
    }

    return EXIT_SUCCESS;
}
