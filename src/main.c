#include "init.h"
#include "add.h"
#include "rm.h"
#include "commit.h"

#include <string.h>
#include <stdio.h>

int cmd_init() {
    return init_repo();
}

void cmd_rm(int argc, char *argv[]) {
    remove_files_from_storage(argv + 2, argc - 2);
}

void cmd_add(int argc, char *argv[]) {
    add(argv + 2, argc - 2);
}

void cmd_commit(int argc, char *argv[]) {
    char *msg = NULL;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0) {
            if (i + 1 < argc) {
                msg = argv[i + 1];
                i++;
            } else {
                fprintf(stderr, "-m requires a message\n");
                return;
            }
        } 
    }

    commit(msg);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: vcc COMMAND [ARGS]\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0)
        cmd_init();
    else if (strcmp(argv[1], "add") == 0)
        cmd_add(argc, argv);
    else if (strcmp(argv[1], "rm") == 0)
        cmd_rm(argc, argv);
    else if (strcmp(argv[1], "commit") == 0)
        cmd_commit(argc, argv);
    else {
        fprintf(stderr, "unkown command\n");
        return 1;
    }

    return 0;
}

