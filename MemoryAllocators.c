#include "MemoryAllocators.h"

#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>

pthread_mutex_t global_memory_lock;
meta_header_t *head;
meta_header_t *tail;

meta_header_t* find_empty_space(size_t);

void* malloc(size_t bytes) {
    void* block_return;

    if (bytes <= 0) {
        return NULL;
    }

    pthread_mutex_lock(&global_memory_lock);
    meta_header_t *free_header = find_empty_space(bytes);

    if (free_header != NULL) {
        pthread_mutex_unlock(&global_memory_lock); // unlocking because done with memory related work
        free_header->status = OCCUPIED;

        /*
         * returning free_header + 1 so that the pointer
         * actually starts from after the header (directly
         * where non-meta-data memory will be stored)
         */

        block_return = (void*) (free_header + 1);
        return block_return; 
    }

    /*  
     *  if we reach here, it means that there was not an empty space found
     *  by find_empty_space() in which case we would need to increase
     * the heap size
     */

    size_t total_size = META_SIZE + bytes;
    block_return = sbrk(total_size); // heap increased by header size + the data size required
                                     // by using the system call making sbrk()

    /*
     * This case is if sbrk() is unable to
     * increase heap size
     */

    if (block_return == (void*) -1) {
        pthread_mutex_unlock(&global_memory_lock);
        return NULL;
    }

    meta_header_t *new_header = block_return;

    /*
     * Setting appropriate metadata of new pointer
     */

    new_header->size = total_size - META_SIZE;
    new_header->status = OCCUPIED;
    new_header->link = NULL;

    if (head == NULL) {
        head = new_header;
        head->link = NULL;
    }

    if (tail == NULL) {
        tail = new_header;
        tail->link = NULL;
    } else {
        tail->link = new_header;
        tail = tail->link;
    }

    pthread_mutex_unlock(&global_memory_lock);

    return (block_return + META_SIZE);
}

meta_header_t* find_empty_space(size_t size) {
    assert(size > 0);
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
