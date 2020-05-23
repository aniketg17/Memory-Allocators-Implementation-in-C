#include "MemoryAllocators.h"

#include <stdio.h>

void* malloc() {
    return NULL;
}

void free(void *ptr) {
    return;
}

void* realloc(void* ptr, size_t bytes) {
    return NULL;
}

void* calloc(size_t elems, size_t size) {
    return NULL;
}

int main() {
    return 0;
}
