#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "clogger.h"

void
test_log(void)
{
        clogger_create(stderr);
        LOG_INFO("info");
        LOG_DEBUG("debug");
        LOG_WARNING("warning");
        LOG_ERROR("error");
}

void
test_log_file(void)
{
        FILE *logs = NULL;

        logs = fopen("logs.txt", "a+");
        if (logs == NULL) {
                LOG_ERROR("%s", strerror(errno));
                exit(EXIT_FAILURE);
        }

        clogger_create(logs);
        LOG_INFO("info message");
        LOG_INFO("info %d", 1);
        LOG_DEBUG("debug message");
        LOG_DEBUG("debug %d", 2);
        LOG_WARNING("warning message");
        LOG_WARNING("warning %d", 3);
        LOG_ERROR("error message");
        LOG_ERROR("error %d", 4);

        fclose(logs);
}

void
custom_flog_info(FILE *stream, const char *format, ...)
{
        va_list args;
        va_start(args, format);

        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer) - 1, format, args);

        clogger_create(stream);
        LOG_INFO("%s", buffer);

        va_end(args);
}

void
custom_flog_debug(FILE *stream, const char *format, ...)
{
        va_list args;
        va_start(args, format);

        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer) - 1, format, args);

        clogger_create(stream);
        LOG_DEBUG("%s", buffer);

        va_end(args);
}

int main(void)
{
        test_log();
        test_log_file();

        FILE *logs = NULL;
        logs = fopen("logs2.txt", "a+");
        if (logs == NULL) {
                LOG_ERROR("%s", strerror(errno));
                exit(EXIT_FAILURE);
        }

        clogger_create(logs);
        custom_flog_info(logs, "wrapping FLOG_INFO in a custom function");
        custom_flog_debug(logs, "wrapping %s in a custom function", "FLOG_DEBUG");

        fclose(logs);

        return EXIT_SUCCESS;
}
