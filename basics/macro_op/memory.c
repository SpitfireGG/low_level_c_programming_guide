// main.c
#define DEBUG_MEMORY  // Enable memory tracking
#include "memory.h"

int main()
{
    char *buffer1 = MALLOC(100);
    char *buffer2 = MALLOC(200);

    // Use buffers...

    FREE(buffer1, 100);
    // Oops, forgot to free buffer2!

    MEMORY_REPORT();  // Will report 200 bytes still allocated
    return 0;
}
