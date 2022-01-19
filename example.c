#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "clogger.h"

void
test_log(void)
{
        clogger_colored_console(ACTIVE);
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

        LOG_INFO_F(logs, "info message");
        LOG_INFO_F(logs, "info %d", 1);
        LOG_DEBUG_F(logs, "debug message");
        LOG_DEBUG_F(logs, "debug %d", 2);
        LOG_WARNING_F(logs, "warning message");
        LOG_WARNING_F(logs, "warning %d", 3);
        LOG_ERROR_F(logs, "error message");
        LOG_ERROR_F(logs, "error %d", 4);

        fclose(logs);
}

void
custom_log_info(FILE *stream, const char *format, ...)
{
        va_list args;
        va_start(args, format);

        char buffer[MSGMAXLENGTH];
        vsnprintf(buffer, sizeof(buffer) - 1, format, args);

        LOG_INFO_F(stream, "%s", buffer);

        va_end(args);
}

void
custom_log_debug(FILE *stream, const char *format, ...)
{
        va_list args;
        va_start(args, format);

        char buffer[MSGMAXLENGTH];
        vsnprintf(buffer, sizeof(buffer) - 1, format, args);

        LOG_DEBUG_F(stream, "%s", buffer);

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

        custom_log_info(logs, "wrapping LOG_INFO_F in a custom function");
        custom_log_debug(logs, "wrapping %s in a custom function", "LOG_DEBUG_F");

        fclose(logs);

        return EXIT_SUCCESS;
}
