#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../clogger.h"

#define NTHREADS 5

typedef struct Threads Threads;
static struct Threads {
        pthread_t thrd[NTHREADS];
} _threadsA, _threadsB;

void tstart(pthread_t *thread, void *(thread_fn)(void *), void *args);
void tjoin(pthread_t *thread);

void *log_info_file_fn(void *arg);

int main(void)
{
        const char *file = "logs.txt";

        for (int i = 0; i < NTHREADS; ++i) {
                tstart(&_threadsA.thrd[i], log_info_file_fn, (void *) file);
                tstart(&_threadsB.thrd[i], log_info_file_fn, (void *) file);
        }

        for (int i = 0; i < NTHREADS; ++i) {
                tjoin(&_threadsA.thrd[i]);
                tjoin(&_threadsB.thrd[i]);
        }

        return EXIT_SUCCESS;
}

void
tstart(pthread_t *thread, void *(thread_fn)(void *), void *args)
{
        pthread_create(thread, NULL, thread_fn, args);
}

void
tjoin(pthread_t *thread)
{
        pthread_join(*thread, NULL);
}

void *
log_info_file_fn(void *arg)
{
        const char *fp = arg;
        if (fp == NULL) {
                LOG_ERROR("file not provided. f = (%s)", fp);
                return NULL;
        }

        LOG_DEBUG("Thread: %ld started", pthread_self());

        const int counter = 5;
        for (int i = 0; i < counter; i++) {
                LOG_INFO_F(fp, "%d info message of thread %ld", i, pthread_self());
                sleep(3);
        }

        LOG_DEBUG("Thread: %ld finished", pthread_self());

        return NULL;
}
