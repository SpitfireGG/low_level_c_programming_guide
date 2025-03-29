#include <stdio.h>

int subtract(int x, int y) { return x - y; }
int add(int x, int y) { return x + y; }

void apply(int (*operation)(int, int), int a, int b) {

    printf("consoling %d\n", operation(a, b));
}

int main() {
    int (*func_ptr)(int, int);
    func_ptr = add;
    printf("%d\n", func_ptr(3, 4));
    apply(add, 10, 20);
    return 0;
}

