#include "sys/types.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BIG 50000000UL
uint32_t counter = 0;
/* atomic_uint counter = ATOMIC_VAR_INIT(0); */ // the atomic way of dealing
                                                // with race condition
pthread_mutex_t lock =
    PTHREAD_MUTEX_INITIALIZER; // using mutex to lock resources

void *countBig(void *arg) {

  for (uint32_t i = 0; i < BIG; i++) {
    pthread_mutex_lock(&lock);
    counter++;
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}
int main() {
  printf("consoling with threading\n");

  pthread_t pthread;
  if (pthread_create(&pthread, NULL, countBig, NULL) != 0) {
    perror("thread create failed\n");
    return 1;
  };

  countBig(NULL);

  if (pthread_join(pthread, NULL) != 0) {
    perror("thread join failed\n");
    return 1;
  };

  printf("counting has finished %u \n", counter);
  return 0;
}
