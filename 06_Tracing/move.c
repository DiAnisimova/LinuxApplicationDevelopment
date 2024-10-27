#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define EXIT_NO_ERROR 0
#define EXIT_WRONG_ARGS 1
#define EXIT_INFILE_OPEN_ERROR 2
#define EXIT_OUTFILE_OPEN_ERROR 3
#define EXIT_READ_ERROR 4
#define EXIT_WRITE_ERROR 5
#define EXIT_CLOSE_INFILE_ERROR 6
#define EXIT_CLOSE_OUTFILE_ERROR 7
#define EXIT_REMOVE_ERROR 8

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *infile = NULL;
    FILE *outfile = NULL;
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        return EXIT_WRONG_ARGS;
    }

    if (0 == strcmp(argv[1], argv[2]))
        return EXIT_NO_ERROR;

    infile = fopen(argv[1], "rb");
    if (infile == NULL) {
        fprintf(stderr, "Error opening %s: %s\n", argv[1], strerror(errno));
        return EXIT_INFILE_OPEN_ERROR;
    }

    outfile = fopen(argv[2], "wb");
    if (outfile == NULL) {
        fprintf(stderr, "Error opening %s: %s\n", argv[2], strerror(errno));
        fclose(infile);
        return EXIT_OUTFILE_OPEN_ERROR;
    }

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, infile)) > 0) {
        fwrite(buffer, 1, bytesRead, outfile);
        if (EOF == fflush(outfile)) {
            fprintf(stderr, "Error writing to output file\n");
            fclose(infile);
            fclose(outfile);
	    remove(argv[2]);
            return EXIT_WRITE_ERROR;
        }
    }

    if (ferror(infile)) {
        fprintf(stderr, "Error reading from input file\n");
        fclose(infile);
        fclose(outfile);
	remove(argv[2]);
        return EXIT_READ_ERROR;
    }

    if (fclose(infile) != 0) {
        fprintf(stderr, "Error closing input file\n");
        fclose(outfile);
        return EXIT_CLOSE_INFILE_ERROR;
    }

    if (fclose(outfile) != 0) {
        fprintf(stderr, "Error closing output file\n");
        return EXIT_CLOSE_OUTFILE_ERROR;
    }

    if (remove(argv[1]) != 0) {
        fprintf(stderr, "Error deleting %s: %s\n", argv[1], strerror(errno));
        return EXIT_REMOVE_ERROR;
    }

    return EXIT_NO_ERROR;
}
