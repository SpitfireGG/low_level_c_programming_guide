#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 10
#define KILL_ANIMAL __attribute__((cleanup()))

typedef struct
{
    char *animal;
    char *habitat;
    uint8_t age;

} Animal;

void freeer(void *ptr_addr)
{
    printf("freeing %p\n", (void *) ptr_addr);
    void **ptr = (void **) ptr_addr;
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

Animal *init_animal(char *name, char *home, uint8_t age)
{
    /*     Animal a = {.animal = "kangaroo", .habitat = "home", .age = 19}; */

    Animal *b = malloc(sizeof(Animal));

    b->animal  = malloc(strlen(name) + 1);
    b->habitat = malloc(strlen(home) + 1);

    strcpy(b->animal, name);
    strcpy(b->habitat, home);

    b->age = age;

    return b;
    /*     kill_animal(str_ptr); */  // gives error , double free
}

int main()
{
    fn1();
    Animal *animal __attribute__((cleanup(freeer))) =
        init_animal("doggy", "shed", 10);

    return 0;
}
