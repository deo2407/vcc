#include "init.h"
#include "add.h"
#include "rm.h"

#include <string.h>
#include <stdio.h>

int cmd_init(const char *argv[]) {
    return init_repo();
}

void cmd_rm(int argc, const char *argv[]) {
    remove_files_from_index(argv + 2, argc - 2);
}

int cmd_add(int argc, const char *argv[]) {
    return add(argv, argc);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: vcc COMMAND [ARGS]\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0)
        cmd_init(argv);
    else if (strcmp(argv[1], "add") == 0)
        cmd_add(argc, argv);
    else if (strcmp(argv[1], "rm") == 0)
        cmd_rm(argc, argv);
    else {
        fprintf(stderr, "unkown command\n");
        return 1;
    }

    return 0;
}

