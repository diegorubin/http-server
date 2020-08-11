#ifndef __SERVER_WORKER_H__
#define __SERVER_WORKER_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct worker_t {
  char busy;
  pid_t proccess;
} worker_t;

typedef worker_t *worker_ptr;

void init_workers(int number_of_workers);
int wait_for_free_worker();

#endif
