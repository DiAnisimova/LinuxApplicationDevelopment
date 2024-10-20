#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAXGR 10
#define MAX_ERR_SIZE 256


int main(int argc, char *argv[]) {
    if (argc < 4) {
	printf("Usage: ./esub <regexp> <pattern> <text>\n");
	return 0;
    }
    regex_t regex;
    regmatch_t bags[MAXGR];
    char errbuf[MAX_ERR_SIZE];
    char *regexp = argv[1];
    char *substitution = argv[2];
    char *string = argv[3];

    int errcode = regcomp(&regex, regexp, REG_EXTENDED);

    if (errcode) {	
        size_t error_len = regerror(errcode, &regex, errbuf, MAX_ERR_SIZE);
        printf("Error: %.*s\n", (int)error_len, errbuf);
        return 0;
    }
    int code = regexec(&regex, string, MAXGR, bags, 0);
    if (code == 0) {
      //  puts(string);
      //  for(int i=0; i<MAXGR && bags[i].rm_so>=0; i++) {
      //      int b = bags[i].rm_so, e = bags[i].rm_eo;
      //      printf("%d %d/%d\t%.*s\n", i, b, e, e - b, string + b);
      //  }

        for (const char *p = substitution; *p != '\0'; ++p) {
            if (*p == '\\' && (*(p + 1) != '\0')) {
                ++p;
                if (*p >= '0' && *p <= '9') {
                    int group_num = *p - '0';
                    if (group_num >= MAXGR || bags[group_num].rm_so == -1) {
                        printf("Invalid back reference: %.*s\n", (int)strlen(substitution), substitution);
                        regfree(&regex);
                        return 0;
                    }
                }
            }
        }
        for (int i = 0; i < bags[0].rm_so; ++i) {
            putchar(string[i]);
        }

        for (const char *p = substitution; *p != '\0'; ++p) {
            if (*p == '\\' && (*(p + 1) != '\0')) {
                ++p;
                if (*p >= '0' && *p <= '9') {
                    int group_num = *p - '0';
                    int start = bags[group_num].rm_so;
                    int end = bags[group_num].rm_eo;
                    for (int i = start; i < end; ++i) {
                        putchar(string[i]);
                    }
                } else if (*p == '\\') {
                    putchar('\\');
                } else {
                    putchar(*p);
                }
            } else {
                putchar(*p);
            }
        }

        for (int i = bags[0].rm_eo; string[i] != '\0'; ++i) {
            putchar(string[i]);
        }

        putchar('\n');

    } else {
	if (code != REG_NOMATCH) {
            size_t error_len = regerror(errcode, &regex, errbuf, MAX_ERR_SIZE);
            printf("Error: %.*s\n", (int)error_len, errbuf);
        } else {
            printf("%s\n", string);
        }
    }

    regfree(&regex);
    return 0;
}
