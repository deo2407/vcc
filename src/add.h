#ifndef ADD_H
#define ADD_H

#include "object.h"
#include <sys/types.h>

void add_obj(const char *filename, char *contents, long size, obj_type_t type);
int add(const char *files[], size_t files_len);

#endif

