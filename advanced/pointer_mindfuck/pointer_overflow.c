#include <stdio.h>

int main(void)
{
    int arr_int[5] = {12, 4, 234, 35, 3};

    printf("%d\n", *(arr_int + 1));

    int *arr_ptr  = arr_int;
    int *arr_ptr1 = &arr_int[1];
    printf("%d\n", *arr_ptr);
    printf("%d\n", *arr_ptr1);

    printf("%p\n", (void *) (arr_ptr + 0));
    printf("%p\n", (void *) (arr_ptr + 1));
    printf("%p\n", (void *) (arr_ptr + 2));  // offset 4

    printf("%p\n", (void *) (arr_ptr + 100));

    int *mid = &arr_int[2];
    printf("%d\n", mid[-2]);  /// pointer arithmetic : *(mid  -2 )
    printf("%d\n", (-2)[mid]);
    printf("%d\n", *(mid - 2));
    printf("%d\n", ((-1)[mid]));

    return 0;
}
