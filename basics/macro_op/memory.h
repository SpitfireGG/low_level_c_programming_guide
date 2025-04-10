// memory.h
#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

#ifdef DEBUG_MEMORY
#    include <stdio.h>

static size_t total_allocated = 0;

#    define MALLOC(size)                                                                       \
        ({                                                                                     \
            void *ptr = malloc(size);                                                          \
            if (ptr) {                                                                         \
                total_allocated += size;                                                       \
                printf("Allocated %zu bytes at %p, total: %zu\n", size, ptr, total_allocated); \
            }                                                                                  \
            ptr;                                                                               \
        })

#    define FREE(ptr, size)                                                                \
        do {                                                                               \
            if (ptr) {                                                                     \
                free(ptr);                                                                 \
                total_allocated -= size;                                                   \
                printf("Freed %zu bytes at %p, total: %zu\n", size, ptr, total_allocated); \
                ptr = NULL;                                                                \
            }                                                                              \
        } while (0)

#    define MEMORY_REPORT() printf("Memory report: %zu bytes still allocated\n", total_allocated)

#else
#    define MALLOC(size) malloc(size)
#    define FREE(ptr, size) \
        do {                \
            free(ptr);      \
            ptr = NULL;     \
        } while (0)
#    define MEMORY_REPORT() ((void)0)
#endif

#endif  // MEMORY_H
