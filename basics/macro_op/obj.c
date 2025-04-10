#include <stdio.h>

#ifndef EMPLOYEES
#define EMPLOYEES                                                              \
    X(john, "john cena", 43)                                                   \
    X(ram, "ramB", 11)                                                         \
    X(some, "somedome", 33)
#endif

typedef enum
{
#define X(id, name, age) id,
    EMPLOYEES
#undef X
        EMPLOYEES_COUNT
} EMP_INFO;

int main()
{
    printf("Number of employees: %d\n", EMPLOYEES_COUNT);
    return 0;
}
