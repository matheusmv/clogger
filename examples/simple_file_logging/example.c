#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../clogger.h"

void
test_log_file(const char *filename)
{
        FILE *logs = NULL;
        if ((logs = fopen(filename, "a+")) == NULL) {
                LOG_ERROR("%s", strerror(errno));
                exit(EXIT_FAILURE);
        }

        LOG_INFO_F(logs, "add random %s message in %s", "info", filename);

        LOG_DEBUG_F(logs, "add random %s message in %s", "debug", filename);

        LOG_WARNING_F(logs, "add random %s message in %s", "warning", filename);

        LOG_ERROR_F(logs, "add random %s message in %s", "error", filename);

        fclose(logs);
}

int main(void)
{
        test_log_file("logs.txt");

        return EXIT_SUCCESS;
}
