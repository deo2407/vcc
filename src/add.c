#include "add.h"
#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void binary_to_hex(const unsigned char *buf, int len, char *out) {
    const char hex[] = "0123456789abcdef";
    for (int i = 0; i < len; i++) {
        out[i * 2] = hex[(buf[i] >> 4) & 0xF];
        out[i * 2 + 1] = hex[buf[i] & 0xF];
    } 
    out[len * 2] = '\0';
}

int add(const char *files[], size_t files_len) {
    for (int i = 2; i < files_len; i++) {
        FILE *fp = fopen(files[i], "rb");

        if (fp == NULL) {
            fprintf(stderr, "could not find file %s\n", files[i]);
            continue;
        }

        fseek(fp, 0L, SEEK_END);
        long length = ftell(fp);
        rewind(fp);

        unsigned char* buffer = (unsigned char*)malloc(length + 1);
        if (!buffer) {
            fclose(fp);
            continue;
        }

        size_t bytesRead = fread(buffer, 1, length, fp);
        buffer[bytesRead] = '\0';
        fclose(fp);

        // create the hash for the given file
        unsigned char hash_bin[SHA_DIGEST_LENGTH];
        char hash[SHA_DIGEST_LENGTH * 2];
        SHA1(buffer, bytesRead, hash_bin);
        binary_to_hex(hash_bin, SHA_DIGEST_LENGTH, hash);

        printf("generated hash for file %s: %s\n", files[i], hash);

        // serialize it
        char *serialized = serialize_file(buffer, bytesRead);

        // store the file
        char filename[128];
        snprintf(filename, sizeof filename, ".vcc/objects/%s", hash);

        fp = fopen(filename, "wb");
        if (fp == NULL) {
            fprintf(stderr, "could not create object file with hash %s\n", hash);
            continue;
        }

        printf("%s added to storage\n", files[i]);

        free(serialized);
        free(buffer);
    }
    return 0;
}

