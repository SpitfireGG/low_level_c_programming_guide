#include "alloca.h"
#include <stdio.h>
#include <stdlib.h>

// Pointers

/*
 reading pointers form right to left is how it is done
 ex : int *arr ; --> defines a arr that is a pointer to an int
*/

// learn more about pointers in -> pointers.md

int main() {

  int age = 25;
  printf("The value of age is: %d\n", age);
  printf("The value &  address of age is: %d, %p via pointer:%p\n", age, &age,
         (void *)&age);

  int salary = 1000000;

  // to hold the memory address, you'll need to first initialize a pointer
  int *sp = &salary;
  // doing something like -> int sp = &salary (invalid, int type is not supposed
  // to hold memory address rather an integer instead )

  // modding values with pointers
  *sp = 100;
  printf("salary is now changed to %d via pointer: %p\n", salary,
         (void *)sp); // no need for void here

  // Arrays & pointers
  /*    arrays in C are closely related to pointers. The name of an array
   * actually operates as a pointer to its first element. */

  int numbers[5] = {10, 20, 30, 40, 50};
  int *p = numbers; // same as int *p = &numbers[0];
  printf("%d\n", *(&p[0]));
  printf("%d\n", *(&p[0] + 1));
  printf("%p\n", (void *)(&p[0] + 2)); // casting with void

  // Multi-pointers
  int someCrap = 7;
  int *fp = &someCrap;
  int **spp = &fp;
  printf("value: %d via pointer %p via pointer %p, last_value: %d\n", someCrap,
         (void *)fp, (void *)spp, **spp);

  // some-generic shit
  void *secondCrap = &someCrap;
  printf("Void casting to other types : %d\n",
         *(int *)secondCrap); // casting type from void(generic to int);

  // ---------------------------------issues related to pointers
  // ----------------------------------------------- Dangling pointers

  // uninitialized ptr
  /* int *lovePtr;
  *lovePtr = 5;
  printf("%d\n", *lovePtr); // uninitialized pointers : seg fault */

  /* int *ptr = (int *)malloc(sizeof(int));
  free(ptr);
  ptr = NULL;
  printf("%d\n", *ptr); // accessing freed block from the memory : seg fault

  // Null pointer dereference
  int *someIntPtr = NULL;
  /*   printf("dereferencing a null pointer %d\n", *someIntPtr); */
  /* if (someIntPtr == NULL) {
     perror("dereferencing a NULL pointer");
     exit(1);
   } */

  return 0;
}
