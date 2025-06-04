#include <stdio.h>

int add(int x, int y);
int mul(int x, int y);

int add(int x, int y)
{
    return x + y;
}

int mul(int x, int y)
{
    return x * y;
}

void function_ptr_insanity()
{
    // make an array of function pointers
    int (*ops[5])(int, int) = {add, mul};

    printf("ops[0] -> %d\n", ops[0](5, 10));
    printf("[0]ops -> %d\n", 0 [ops](5, 10));

    printf("ops[1] -> %d\n", ops[1](50, 20));
    printf("[1]ops -> %d\n", 1 [ops](50, 20));

    int (*func_ptr)(int, int) = add;
    printf("%d\n", (func_ptr) (10, 20));
    printf("%d\n", (*func_ptr)(10, 20));
    printf("%d\n", (**func_ptr)(10, 20));
    printf("%d\n", (***func_ptr)(10, 20));
    printf("%d\n", (****func_ptr)(10, 20));
    printf("%d\n", (****func_ptr)(10, 20));
    printf("%d\n", (******func_ptr)(10, 20));
}

int main()
{
    function_ptr_insanity();
    return 0;
}
