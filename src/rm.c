#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rm.h"

#define INDEX_FILE ".vcc/index"
#define TEMP_FILE  ".vcc/index_tmp"

// Remove lines containing a specific substring from the index file
int remove_file_from_index(const char *filename) {
    FILE *index_fp = fopen(INDEX_FILE, "r");
    if (!index_fp) {
        perror("Could not open index file for reading");
        return -1;
    }

    FILE *temp_fp = fopen(TEMP_FILE, "w");
    if (!temp_fp) {
        perror("Could not open temporary file for writing");
        fclose(index_fp);
        return -1;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int found = 0;

    while ((read = getline(&line, &len, index_fp)) != -1) {
        // Skip lines containing the filename
        if (strstr(line, filename) != NULL) {
            found = 1;
            continue;
        }
        fputs(line, temp_fp);
    }

    free(line);
    fclose(index_fp);
    fclose(temp_fp);

    // Replace original index with temp file
    if (remove(INDEX_FILE) != 0) {
        perror("Failed to remove original index file");
        return -1;
    }
    if (rename(TEMP_FILE, INDEX_FILE) != 0) {
        perror("Failed to rename temp file to index file");
        return -1;
    }

    printf("removed file %s from index\n", filename);
    return found ? 0 : -1;
}

// Remove multiple files from the index
void remove_files_from_index(const char *files[], int size) {
    for (int i = 0; i < size; i++) {
        if (remove_file_from_index(files[i]) != 0) {
            fprintf(stderr, "File not found in index: %s\n", files[i]);
        }
    }
}

