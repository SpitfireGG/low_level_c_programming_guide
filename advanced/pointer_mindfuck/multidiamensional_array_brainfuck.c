#include <stdio.h>

void multidimensional_madness()
{
    int arr[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    printf("%d\n", arr[1][2]);                 // prints 7
    printf("%d\n", *(*(arr + 1) + 2));         // 7
    printf("%d\n", *((int *) (arr + 1) + 2));  // 7
    printf("%d\n", (*(int *) (arr) + 6));      // 7

    int(*ptr_to_row)[4] = arr;  // Points to first row

    printf("%d\n", (ptr_to_row)[2][3]);
    printf("%d\n", (ptr_to_row + 1)[1][3]);
}
int main(void)
{
    multidimensional_madness();
    return 0;
}
