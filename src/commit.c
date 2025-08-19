#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

char *build_msg(char *hash, char *msg) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char time_buf[64];
    strftime(time_buf, sizeof time_buf, "%Y-%m-%d %H:%M:%S %z", local);

    size_t len = 512 + strlen(msg) + strlen(time_buf) + 1;
    char *commit_msg = malloc(len);

    if (!commit_msg) return NULL;

    snprintf(commit_msg, len, "tree %s\n%s\n\n%s", hash, time_buf, msg);

    return commit_msg;
}

void commit(char *msg) {
    char hash[SHA_DIGEST_LENGTH*2 + 1];
    if (build_tree(hash, sizeof hash) != 0)
        return;

    
    char *commit_msg = build_msg(hash, msg);

    // generate filepath
    get_hash(commit_msg, sizeof commit_msg, hash, sizeof hash); 
    char filepath[512];
    snprintf(filepath, sizeof filepath, ".vcc/objects/%s", hash); 

    FILE *fp = fopen(filepath, "wb");

    fprintf(fp, "%s", commit_msg);

    // update HEAD file
    fp = fopen(".vcc/refs/heads/master", "wb");
    fprintf(fp, "%s", hash);

    fp = fopen(".vcc/HEAD", "wb");
    fprintf(fp, "ref: refs/heads/master");

    fclose(fp);
    free(commit_msg);
}
