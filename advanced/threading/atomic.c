#include <stdatomic.h>
#include <stdio.h>

_Atomic int counter = ATOMIC_VAR_INIT(0);

int main() {

  int value = atomic_load(&counter);
  printf("%d\n", value);

  atomic_store(&counter, 233);
  atomic_load(&counter);

  printf("%d\n", value);
  return 0;
}
