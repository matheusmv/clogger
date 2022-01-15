#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "clog.h"

void
test_log(void)
{
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

        FLOG_INFO(logs, "info message");
        FLOG_INFO(logs, "info %d", 1);

        FLOG_DEBUG(logs, "debug message");
        FLOG_DEBUG(logs, "debug %d", 2);

        FLOG_WARNING(logs, "warning message");
        FLOG_WARNING(logs, "warning %d", 3);

        FLOG_ERROR(logs, "error message");
        FLOG_ERROR(logs, "error %d", 4);

        fclose(logs);
}

void
custom_flog_info(FILE *stream, const char *format, ...)
{
        va_list args;
        va_start(args, format);

        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer) - 1, format, args);

        FLOG_INFO(stream, "%s", buffer);

        va_end(args);
}

void
custom_flog_debug(FILE *stream, const char *format, ...)
{
        va_list args;
        va_start(args, format);

        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer) - 1, format, args);

        FLOG_DEBUG(stream, "%s", buffer);

        va_end(args);
}

int main(int argc, char *argv[])
{
        test_log();
        test_log_file();

        FILE *logs = NULL;
        logs = fopen("logs.txt", "a+");
        if (logs == NULL) {
                LOG_ERROR("%s", strerror(errno));
                exit(EXIT_FAILURE);
        }

        custom_flog_info(logs, "wrapping FLOG_INFO in a custom function");
        custom_flog_debug(logs, "wrapping %s in a custom function", "FLOG_DEBUG");

        fclose(logs);

        return EXIT_SUCCESS;
}
