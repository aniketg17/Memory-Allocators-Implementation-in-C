#ifndef MEMORYALLOCATORS_H
#define MEMORYALLOCATORS_H

#include <stddef.h>

void* malloc(size_t);
void free(void*);
void* realloc(void*, size_t);
void* calloc(size_t, size_t);

#endif // MEMORYALLOCATORS_H
