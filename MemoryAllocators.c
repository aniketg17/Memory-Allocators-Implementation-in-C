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
    block_return = sbrk(total_size); // heap increased by using the system call from sbrk()

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

    new_header->size = bytes;
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
    meta_header_t *traverse = head;
    while (traverse != NULL) {
        if (traverse->status == FREE && traverse->size >= size) {
            return traverse;
        }
        traverse = traverse->link;
    }
    return traverse;
}

void free(void *ptr) {
    // 2 cases: either at the end of a heap OR in between somewhere

    if (ptr == NULL) {
        return;
    }

    pthread_mutex_lock(&global_memory_lock);

    void* current_heap_height = sbrk(0);

    meta_header_t *linked_header = (meta_header_t*) ptr - 1;

    if (current_heap_height == ((char*) ptr) + linked_header->size) { // casted to char to 
        //ensure pointer addition 
        //is by correct units

        /*
         * This means that the memory to remove is at end of heap
         */

        sbrk(0 - linked_header->size - META_SIZE);

        if (head == tail) {
            head = NULL;
            tail = NULL;
        } else {
            meta_header_t *traverse = head;

            while (traverse->link != NULL) { // traversing till null in case passed in pointer was externally malloc'ed
                if (traverse->link == linked_header) {
                    traverse->link = NULL;
                    tail = traverse;
                    break;
                }
                traverse = traverse->link;
            }
        }
        pthread_mutex_unlock(&global_memory_lock);
        return;
    } else {
        meta_header_t *traverse = head;

        while (traverse->link != NULL) { // traversing till null in case passed in pointer was externally malloc'ed
            if (traverse->link == linked_header) {
                traverse->link->status = FREE;
                break;
            }
            traverse = traverse->link;
        }

        pthread_mutex_unlock(&global_memory_lock);
        return;
    }
}

void* realloc(void* ptr, size_t bytes) {
    return NULL;
}

void* calloc(size_t count, size_t size) {
    return NULL;
}

int main() {
    //printf("%lu size_t %lu signed %lu unsigned\n", sizeof(size_t), sizeof(signed), sizeof(unsigned));

    int *a = malloc(8);

    printf("%lu\n", sizeof(a));

    for (int i = 0; i < 8; i++) {
        a[i] = 94;
    }

    for (int i = 0; i < 8; i++) {
        printf("%d\n", a[i]);
    }

    printf("end\n");

    free(a);

    printf("%lu\n", sizeof(a));
}
