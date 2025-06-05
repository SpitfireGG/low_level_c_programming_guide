#include <stddef.h>
#include <stdio.h>
#include "signal.h"

int main(void)
{
    int x       = 100;
    int _hx     = 0x12345678;
    void *x_ptr = &x;
    /*     void *_hx_ptr = &_hx; */

    void *ptr_addr = (void *) x_ptr;
    printf("%p\n", ptr_addr);

    unsigned int UI32 = *(unsigned int *) x_ptr;
    printf("%u\n", UI32);

    float F32 = *(float *) x_ptr;
    printf("%f\n", F32);

    float D64 = *(double *) x_ptr;
    printf("%f\n", D64);

    char ch = *(char *) x_ptr;
    printf("%c\n", ch);

    unsigned char *chh = (unsigned char *) &_hx;

    printf("bytes:");
    for (size_t i = 0; i < sizeof(int); i++)
    {
        printf("%02x ", chh[i]);
    }
    putchar('\n');

    printf("first byte as an int %d\n",
           *(int *) ((char *) &_hx + 0));  // add 1 and see what happens ??

    return 0;
}
