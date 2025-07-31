#include "init.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int init_repo() {
    struct stat st = {0};

    if (stat(".vcc", &st) == -1) {
        if (mkdir(".vcc", 0700) == -1) {
            fprintf(stderr, "Error creating .vcc: %s\n", strerror(errno));
            return 1;
        }

        if (mkdir(".vcc/objects", 0700) == -1) {
            fprintf(stderr, "Error creating .vcc/objects: %s\n", strerror(errno));
            return 1;
        }

        if (mkdir(".vcc/refs", 0700) == -1) {
            fprintf(stderr, "Error creating .vcc/refs: %s\n", strerror(errno));
            return 1;
        }

        FILE *fp = fopen(".vcc/HEAD", "w");
        if (fp == NULL) {
            fprintf(stderr, "Unable to create file HEAD\n");
            return 1;
        }
        fclose(fp);
    } else {
        printf(".vcc directory already exists\n");
    }
    
    printf("repo initialized\n");
    return 0;
}

