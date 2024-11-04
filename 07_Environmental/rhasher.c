#include <rhash.h>
#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void hash_and_print(const char *algorithm, const char *input) {
    unsigned char buffer[64]; // Buffer for hash output
    char output[256]; // Buffer for formatted output
    size_t output_length;
    int hash_id = 0;

    if (strcasecmp(algorithm, "MD5") == 0) {
        hash_id = RHASH_MD5;
    } else if (strcasecmp(algorithm, "SHA1") == 0) {
        hash_id = RHASH_SHA1;
    } else if (strcasecmp(algorithm, "TTH") == 0) {
        hash_id = RHASH_TTH;
    } else {
        fprintf(stderr, "Unsupported hash algorithm: %s\n", algorithm);
        return;
    }

    rhash_library_init();

    if (input[0] == '"') {
        size_t length = strlen(input);
        if (input[length - 1] == '"') {
            length--; // Remove the trailing quotation mark
        }
        rhash_msg(hash_id, input + 1, length - 1, buffer);
    } else {
        if (rhash_file(hash_id, input, buffer) < 0) {
            perror("Failed to hash file");
            return;
        }
    }

    if (isupper(algorithm[0])) {
        output_length = rhash_print_bytes(output, buffer, rhash_get_digest_size(hash_id), RHPR_HEX);
    } else {
        output_length = rhash_print_bytes(output, buffer, rhash_get_digest_size(hash_id), RHPR_BASE64);
    }
    printf("%s\n", output);
}

int main() {
    char *line = NULL;

#ifndef USE_READLINE
    size_t len = 0;
#endif

    while (1) {
#ifdef USE_READLINE
        if (isatty(0))
            line = readline("> ");
	else {
	    rl_outstream = stderr;
            line = readline("");
	}
        if (!line) {
            break;
        }
        add_history(line);
#else
	size_t line_length = -1;
        if (isatty(0))
            printf("> ");
        if ((line_length = getline(&line, &len, stdin)) == -1) {
            break;
        }
	line[line_length - 1] = '\0'; // Handle behaviour difference between readline and getline
#endif
        char *token = strtok(line, " ");
        if (!token) {
            fprintf(stderr, "Invalid input format\n");
            continue;
        }

        char *algorithm = token;
        token = strtok(NULL, "");
        if (!token) {
            fprintf(stderr, "Invalid input format\n");
            continue;
        }

        char *input = token;
        hash_and_print(algorithm, input);

#ifdef USE_READLINE
        free(line);
#endif
    }

    free(line);
    return 0;
}
