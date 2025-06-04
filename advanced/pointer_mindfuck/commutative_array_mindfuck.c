#include <stdio.h>

int main()
{
    // make an array of 10 ints
    int array[10] = {3, 543, 54, 35, 45, 3453, 453, 54, 3, 434};

    printf("%d\n", *(array + 1));
    printf("%d\n",
           array[1]);  // both performs the same thing ( the difference is that
                       // , this will be converted or decays into *int by the
                       // compiler, making it *(array + 1 ))

    printf("%d\n", 1 [array]);  // wtf this is also 543, why ??
    // cuz after the decay it   becomes *(1 + array ) this is the same things as
    // adding 1 + 2  and 2 + 1 , both results to 4

    return 0;
}
