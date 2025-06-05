#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 10

typedef struct
{
    char *animal;
    char *habitat;
    uint8_t age;

} Animal;

void freeer(char **ptr)
{
    printf("freeing %p\n", (void *) *ptr);
    free(*ptr);
    *ptr = NULL;
}

void kill_animal(Animal *an)
{
    printf("killing << %p >> animal %s\n", (void *) an, an->animal);
    free(an->animal);
    an = NULL;
}

void fn1()
{
    char *buffer __attribute__((cleanup(freeer))) = malloc(sizeof(char) * 10);

    memset(buffer, 0, BUF_SIZE);
    for (size_t i = 0; i < BUF_SIZE; i++)

    {
        buffer[i] += 2;
    }
    printf("allocate 10 bytes on the heap %p\n", (void *) buffer);
}

void init_animal(char *name, char *home, uint8_t age)
{
    /*     Animal a = {.animal = "kangaroo", .habitat = "home", .age = 19}; */

    Animal b = {NULL, NULL, 0};

    b.animal  = malloc(strlen(name) + 2);
    b.habitat = malloc(strlen(home) + 2);

    strcpy(b.animal, name);
    strcpy(b.habitat, home);

    b.age = age;

    Animal *str_ptr = &b;

    kill_animal(&b);
    /*     kill_animal(str_ptr); */  // gives error , double free
}

int main()
{
    fn1();
    init_animal("elephant", "home", 10);

    return 0;
}
