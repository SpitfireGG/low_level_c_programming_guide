#include <stdio.h>
#include <stdlib.h>

void freeer(char **ptr)
{
    printf("freeing %p\n", (void *) *ptr);
    free(*ptr);
}

void fn1()
{
    char *buffer = malloc(sizeof(char) * 10);
    for (size_t i = 0; i < sizeof buffer; i++)

    {
        buffer[i] += 2;
    }
    printf("allocate 10 bytes on the heap %p\n", (void *) buffer);

    freeer(&buffer);
}

int main()
{
    fn1();

    return 0;
}
