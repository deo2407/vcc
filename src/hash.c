#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char *generate_hash(const char *blob, size_t blob_size) {
    char *hash = (char *)malloc(blob_size);

    return hash;
}
