#ifndef MEMORYALLOCATORS_H
#define MEMORYALLOCATORS_H

#include <stddef.h>
#include <pthread.h>

#define FREE 0
#define OCCUPIED 1
#define META_SIZE sizeof(meta_header_t)

/*
 * Using a linked list structure to keep track
 * of data chunks that may not be contiguous.
 * 
 * @Param: link stores the next or previous
 * pointer in the linked list.
 *
 * @Param: status represents whether a node
 * is available to be used
 *
 * @Param: size stores the amount of size
 * required for a block excluding the header
 * itself.
 */

typedef struct meta_header {
    struct header* link;
    int status;
    size_t size;
} meta_header_t;

void* malloc(size_t);
void free(void*);
void* realloc(void*, size_t);
void* calloc(size_t, size_t);

extern pthread_mutex_t global_memory_lock; // used to keep processes thread-safe
extern meta_header_t *head;
extern meta_header_t *tail;


#endif // MEMORYALLOCATORS_H
