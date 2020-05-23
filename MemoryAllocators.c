#include "MemoryAllocators.h"

#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>

pthread_mutex_t global_malloc_t;
meta_header_t *head;
meta_header_t *tail;

void* malloc(size_t bytes) {
    if (bytes <= 0) {
        return NULL;
    }
    return NULL;
}

meta_header_t* find_empty_space(size_t size) {
    meta_header_t *traverse = head;
    while (traverse != NULL) {
        if (traverse->status == FREE && traverse->size >= size) {
            return traverse;
        }
    }
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
    //printf("%lu size_t %lu signed %lu unsigned\n", sizeof(size_t), sizeof(signed), sizeof(unsigned));
    
    printf("%lu\n",sizeof(meta_header_t));
}
