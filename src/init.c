#include "init.h"

#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void init_repo() {
    struct stat st = {0};

    if (stat(".vcc", &st) == -1) {
        mkdir(".vcc", 0700);
        printf("repo initialized\n");
    } else {
        printf(".vcc directory already exists\n");
    }

}
