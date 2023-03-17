#define _POSIX_C_SOURCE 200809L

#include "clogger.h"

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ISO_DATETIME_FORMAT "%Y-%m-%dT%H:%M:%S%z"

typedef struct clogger {
        FILE            *output;
        bool            colored;
        bool            initialized;
        pthread_mutex_t mutex;
} clogger_t;

static clogger_t prv_logger;

static char *log_type_string_table[][2] = {
        [INFO]  = {"INFO ", "\x1B[32mINFO\033[0m "},
        [DEBUG] = {"DEBUG", "\x1B[34mDEBUG\033[0m"},
        [WARN]  = {"WARN ", "\x1B[33mWARN\033[0m "},
        [ERROR] = {"ERROR", "\x1B[31mERROR\033[0m"}
};

static char *
log_type_to_string(log_type_t type, bool colored)
{
        return log_type_string_table[type][colored];
}

static void
clogger_mutex_init(clogger_t *clogger)
{
        assert(pthread_mutex_init(&clogger->mutex, NULL) == 0);
}

static void
clogger_mutex_lock(clogger_t *clogger)
{
        assert(pthread_mutex_lock(&clogger->mutex) == 0);
}

static void
clogger_mutex_unlock(clogger_t *clogger)
{
        assert(pthread_mutex_unlock(&clogger->mutex) == 0);
}

static clogger_t
clogger_new(void)
{
        clogger_t new_logger = (clogger_t) {
                .output      = stderr,
                .colored     = false,
                .initialized = true
        };

        clogger_mutex_init(&new_logger);

        return new_logger;
}

static void
clogger_log(FILE *stream, const char *time, const char *log_level,
            const char *filename, const char *function, int line,
            const char *format, va_list args)
{
        char message[MSGMAXLENGTH];

        vsnprintf(message, sizeof(message), format, args);
        fprintf(stream, "%s %s %s:'%s':%d - %s\n", time, log_level, filename,
                function, line, message);
}

static void
clogger_init(void)
{
        prv_logger = clogger_new();
        clogger_mutex_lock(&prv_logger);

#if defined(LCOLOR)
        prv_logger.colored = true;
#endif

        clogger_mutex_unlock(&prv_logger);
}

static int
format_datetime_to_iso(struct tm *time_info, char *dest, size_t dest_size)
{
        if (time_info == NULL || dest == NULL || dest_size == 0) {
                return -1;
        }

        size_t required_size = strftime(NULL, 0, ISO_DATETIME_FORMAT, time_info);
        if (required_size >= dest_size) {
                return -1;
        }

        if (strftime(dest, dest_size, ISO_DATETIME_FORMAT, time_info) == 0) {
                return -1;
        }

        return 0;
}

static void
get_time(char *dest, size_t dest_size)
{
        time_t current_time = time(NULL);
        struct tm time_info;

        if (gmtime_r(&current_time, &time_info) == NULL) {
                perror("gmtime_r");
                return;
        }

        if (format_datetime_to_iso(&time_info, dest, dest_size) != 0) {
                fprintf(stderr, "failed to format datetime");
                return;
        }
}

void
clogger(log_type_t type, const char *filename, const char *function,
        int line, const char *format, ...)
{
        if (!prv_logger.initialized) {
                clogger_init();
        }

        va_list args;

        char date_time[32];

        clogger_mutex_lock(&prv_logger);

        va_start(args, format);

        get_time(date_time, sizeof(date_time));

        char *log_type_str = log_type_to_string(type, prv_logger.colored);
        clogger_log(prv_logger.output, date_time, log_type_str, filename,
                    function, line, format, args);

        va_end(args);

        clogger_mutex_unlock(&prv_logger);
}

void
clogger_f(log_type_t type, const char *filepath, const char *filename,
          const char *function, int line, const char *format, ...)
{
        if (!prv_logger.initialized) {
                clogger_init();
        }

        va_list args;

        char date_time[32];

        clogger_mutex_lock(&prv_logger);

        FILE *file = fopen(filepath, "a");
        if (file == NULL) {
                fprintf(stderr, "%s - %s\n", strerror(errno), filepath);
                clogger_mutex_unlock(&prv_logger);
                return;
        }

        va_start(args, format);

        get_time(date_time, sizeof(date_time));

        char *log_type_str = log_type_to_string(type, false);
        clogger_log(file, date_time, log_type_str, filename, function, line,
                    format, args);

        va_end(args);

        fclose(file);

        clogger_mutex_unlock(&prv_logger);
}
