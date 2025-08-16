#include "object.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// "blob CONTENT_SIZE\n" + content
char *serialize_obj(char *content, size_t content_size, obj_type_t type) {
    const char *type_str = (type == BLOB) ? "blob" : "tree";

    char header[64];
    int header_size = snprintf(header, sizeof header, "%s %zu\n", type_str, content_size);
    
    size_t out_size = header_size + content_size;
    char *serialized = (char *)malloc(out_size);
    if (!serialized)
        return NULL;

    memcpy(serialized, header, header_size);
    memcpy(serialized + header_size, content, content_size);

    return serialized;
}
