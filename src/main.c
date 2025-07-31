#include "init.h"

#include <string.h>
#include <stdio.h>

int cmd_init(const char *argv[]) {
    return init_repo();
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: vcc COMMAND [ARGS]\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0)
        cmd_init(argv);
    else {
        fprintf(stderr, "unkown command\n");
        return 1;
    }

    return 0;
}
