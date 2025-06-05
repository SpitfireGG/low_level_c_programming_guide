#include <stdio.h>

typedef struct
{
    int On;
    int Off;
    int Restart;
    int Shutdown;
} State;

int main(void)
{
    State s = {1, 2, 3, 4};
    printf("%d %d %d %d\n", s.On, s.Off, s.Restart, s.Shutdown);

    char *s_ptr = (char *) &s;
    printf("%d\n", *(s_ptr + 4));  // works by the offest of 4 for char
    printf("%d\n", *(s_ptr + 8));

    int *si_ptr = (int *) &s;
    printf("%d\n", *(si_ptr + 1));  // works by the offest of 1 for int
    printf("%d\n", *(si_ptr + 2));
    printf(
        "%d %d\n", si_ptr[1], si_ptr[2]);  // treating arrays like structs ???

    int *str_mem_ptr = &s.On;
    printf("%d\n", *(str_mem_ptr + 1));
    printf("%d\n", *(str_mem_ptr + 2));

    return 0;
}
