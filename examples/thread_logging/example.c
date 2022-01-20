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

void tstart(pthread_t *thread, const char *filepath);
void tjoin(pthread_t *thread);

void *
thread_log_fn(void *arg)
{
        const char *fp = arg;
        if (fp == NULL) {
                LOG_ERROR("file not provided. f = (%s)", fp);
                return NULL;
        }

        const int counter = 10;
        for (int i = 0; i < counter; i++) {
                LOG_INFO_F(fp, "%d info message of thread %ld", i, pthread_self());
                sleep(3);
        }

        return NULL;
}

int main(void)
{
        const char *filepath = "logs.txt";

        for (int i = 0; i < NTHREADS; i++)
                tstart(&_threadsA.thrd[i], filepath);

        for (int i = 0; i < NTHREADS; i++)
                tjoin(&_threadsA.thrd[i]);

        return EXIT_SUCCESS;
}

void
tstart(pthread_t *thread, const char *filepath)
{
        pthread_create(thread, NULL, thread_log_fn, (void *) filepath);
}

void
tjoin(pthread_t *thread)
{
        pthread_join(*thread, NULL);
}
