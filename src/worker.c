#include "worker.h"

worker_t **workers;

void init_workers(int number_of_workers) {
  workers = (worker_t **)calloc(number_of_workers, sizeof(worker_ptr));
  for (int i = 0; i < number_of_workers; i++) {

    pid_t pid = fork();

    if (pid == 0)
      break;

    printf("starting worker %d\n", pid);

    worker_t *worker = malloc(sizeof(worker_t));
    worker->busy = 0;
    workers[i] = worker;
  }
}
