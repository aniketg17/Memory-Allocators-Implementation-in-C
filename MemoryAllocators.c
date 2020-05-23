#include "MemoryAllocators.h"

#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>

pthread_mutex_t global_malloc_t;

void* malloc() {
    return NULL;
}

void free(void *ptr) {
    return;
}

void* realloc(void* ptr, size_t bytes) {
    return NULL;
}

void* calloc(size_t count, size_t size) {
    return NULL;
}

int main() {
    printf("%lu size_t %lu signed %lu unsigned\n", sizeof(size_t), sizeof(signed), sizeof(unsigned));
}
