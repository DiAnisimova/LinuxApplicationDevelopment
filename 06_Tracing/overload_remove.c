#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>

int remove(const char *fname) {
    static int (*original_remove)(const char *) = NULL;

    original_remove = dlsym(RTLD_NEXT, "remove");

    if (strstr(fname, "PROTECT") != NULL) {
        fprintf(stderr, "Protected file: cannot remove '%s'\n", fname);
        errno = EPERM; // Operation not permitted
        return -1;
    }

    return original_remove(fname);
}

FILE* fopen(const char* fname, const char* modeopen) {
    static FILE* (*original_fopen)(const char *, const char *) = NULL;

    original_fopen = dlsym(RTLD_NEXT, "fopen");
    FILE* file;

    if (strstr(fname, "PROTECT") != NULL
            && modeopen != NULL
            && modeopen[0] == 'w'
	    && NULL != (file = original_fopen(fname, "r"))) {
        fprintf(stderr, "Protected file: cannot fopen '%s'\n", fname);
	fclose(file);
        errno = EPERM; // Operation not permitted
        return NULL;
    }

    return original_fopen(fname, modeopen);
}
