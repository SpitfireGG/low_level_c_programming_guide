#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* void *thread_func(void *arg) {

  printf("hello from the thread\n");
  return NULL;
}

int main() {
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, thread_func, NULL);
  pthread_join(thread_id, NULL);
  return 0;
}

*/

void *func1(void *arg) {
    int *ptr = (int *)arg;
    for (int i = 0; i <= 10; i++) {
        sleep(1);
        printf("hello from func1 , val : %d\n", *ptr);
        (*ptr)++;
    }
    return ptr;
}
void func2() {
    for (int x = 1; x <= 5; x++) {
        sleep(1);
        printf("hello from func2 , val : %d\n", x);
    }
}

int main() {

    int v = 1;
    int *result;
    pthread_t pthread;

    pthread_create(&pthread, NULL, func1, &v);

    func2();
    pthread_join(pthread, (void *)&result);
    printf("threading done %d\nresult :%d", v, *result);
    return 0;
}
