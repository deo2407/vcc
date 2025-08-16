#ifndef OBJECT_H
#define OBJECT_H

#include <sys/types.h>

typedef enum {
    BLOB,
    TREE,
} obj_type_t;

char *serialize_obj(char *contents, size_t content_size, obj_type_t type);
void generate_hash_filename(char *contents, long contents_size, char *buf, size_t buf_size);
void get_hash(char *contents, long contents_size, char *buf, size_t buf_size);

#endif
