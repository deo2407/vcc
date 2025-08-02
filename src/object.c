#include "object.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// "blob CONTENT_SIZE\n" + content
char *serialize_file(unsigned char *content, size_t content_size) {
    const char *type = "blob";
    char header[64];
    int header_size = snprintf(header, sizeof header, "%s %zu\n", type, content_size);
    
    size_t out_size = header_size + content_size;
    char *serialized = (char *)malloc(out_size);
    if (!serialized)
        return NULL;

    memcpy(serialized, header, header_size);
    memcpy(serialized + header_size, content, content_size);

    return serialized;
}
