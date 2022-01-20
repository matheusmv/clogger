#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../clogger.h"

#define NTHREADS 10

typedef struct Threads Threads;
static struct Threads {
        pthread_t thrd[NTHREADS];
} _threadsA;

void tstart(pthread_t *thread, void *arg);
void tjoin(pthread_t *thread);

void *
thread_log_fn(void *arg)
{
        FILE *f = arg;
        if (f == NULL) {
                LOG_ERROR("file not provided. f = (%s)", f);
                return NULL;
        }

        const int counter = 10;
        for (int i = 0; i < counter; i++) {
                LOG_INFO_F(f, "%d info message of thread %ld", i, pthread_self());
                sleep(3);
        }

        return NULL;
}

int main(void)
{
        FILE *logs = NULL;
        if ((logs = fopen("logs.txt", "a+")) == NULL) {
                LOG_ERROR("%s", strerror(errno));
                return EXIT_FAILURE;
        }

        for (int i = 0; i < NTHREADS; i++)
                tstart(&_threadsA.thrd[i], logs);

        for (int i = 0; i < NTHREADS; i++)
                tjoin(&_threadsA.thrd[i]);

        fclose(logs);

        return EXIT_SUCCESS;
}

void
tstart(pthread_t *thread, void *arg)
{
        pthread_create(thread, NULL, thread_log_fn, arg);
}

void
tjoin(pthread_t *thread)
{
        pthread_join(*thread, NULL);
}
