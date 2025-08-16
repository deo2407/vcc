#include "tree.h"
#include "object.h"
#include "add.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

const char *mode_to_string(obj_mode_t m) {
    switch (m) {
        case MODE_BLOB_REG:  return "100644";
        case MODE_BLOB_EXEC: return "100755";
        case MODE_TREE:      return "040000";
        case MODE_SYMLINK:   return "120000";
    }
    return "100644"; 
}

size_t compute_tree_body_len(FILE *fp) {
    size_t total = 0;
    
    ssize_t read;
    char *line = NULL;
    size_t len;;
    char entry_str[512];

    while ((read = getline(&line, &len, fp)) != -1)
        total += snprintf(entry_str, sizeof entry_str, "%s blob %s\n", mode_to_string(MODE_BLOB_REG), line);
    
    rewind(fp);

    return total;
}

// TODO!!
void build_tree() {
    FILE *fp = fopen(".vcc/index", "rb");
    if (fp == NULL) {
        fprintf(stderr, "could not open index file!\n");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    long size = 0;
    ssize_t read = 0;
    
    char entry_str[512];
    size_t tree_body_len = compute_tree_body_len(fp);
    char *content = (char *)malloc(tree_body_len + 1);

    while ((read = getline(&line, &len, fp)) != -1) {
        sprintf(entry_str, "%s blob %s\n", mode_to_string(MODE_BLOB_REG), line);
        strcat(entry_str, content);
    }
    add_obj("", content, tree_body_len, TREE); 

    fclose(fp);

    if (line)
        free(line);
}

