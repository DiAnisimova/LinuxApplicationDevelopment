#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <libintl.h>

#define _(STRING) gettext(STRING)

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("guess", LOCALEDIR);
    textdomain("guess");

    int low = 1;
    int high = 100;
    int guess;
    char answer[16384];

    printf(_("Think of a number between 1 and 100.\n"));

    while (low <= high) {
        guess = (low + high) / 2;
        printf(_("Is your number greater than %d? (yes/no): "), guess);
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
            printf(_("Your number is %d!\n"), low);
            break;
        }
    }

    return 0;
}
