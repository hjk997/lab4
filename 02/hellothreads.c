/* pthread argument passsing example */
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

void *hello_thread(void *arg) {
  printf("Thread : Hello, World\n");
  return arg;
}

void main() {
  pthread_t tid[NUM_THREADS];
  int i, status;

  /* create thread */
  for( i = 0; i < NUM_THREADS ; i++){
    status = pthread_create(&tid[i], NULL, hello_thread, (void *)i);
    if (status != 0) {
      fprintf(stderr, "Create thread %d : %d ", i , status);
      exit(1);
    }
  }
  pthread_exit(NULL);
}
