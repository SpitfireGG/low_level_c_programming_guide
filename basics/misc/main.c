#include <stdio.h>

int main()
{
    printf("%s%c|\n", "something has to be printed", 0x00);
    printf("%s %c|\n", "something has to be printed", 0x0D);
    printf("%s%c|\n", "something has to be printed", 0x09);
    printf("%s%c|\n", "something has to be printed", 0x0a);
    printf("%s%c|\n", "something has to be printed", 0x0D);
    printf("%s%c|\n", "something has to be printed", 0x8);
    printf("%s%c|\n", "something has to be printed", 0x1b);
    printf("%s%c|\n", "something has to be printed", 0x7F);

    return 0;
}

