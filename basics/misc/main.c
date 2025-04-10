#include <stdio.h>
#include <stdlib.h>

#include "locale.h"

#define DEBUG 0x001
#define DEBUG_MEMORY

#ifndef BUF_SIZE
#    define BUF_SIZE 256

#endif /* ifndef BUF_SIZE \
#define BUF_SIZE 256 */

int main()
{

#ifdef DEBUG
    printf("the macro is already defined  with bit  set to %d\n", DEBUG);
#endif /* ifdef DEBUG */

    printf("the BUF_SIZE is set to %d\n", BUF_SIZE);
    return 0;

    char *buffer  = malloc(sizeof(char) * 100);
    char *buffer1 = malloc(sizeof(char) * 100);

    FREE(buffer, 100);

    MEMORY_REPORT();
}
