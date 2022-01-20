#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../clogger.h"

void
test_log_file(const char *filename)
{
        LOG_INFO_F(filename, "add random %s message in %s", "info", filename);

        LOG_DEBUG_F(filename, "add random %s message in %s", "debug", filename);

        LOG_WARNING_F(filename, "add random %s message in %s", "warning", filename);

        LOG_ERROR_F(filename, "add random %s message in %s", "error", filename);
}

int main(void)
{
        test_log_file("logs.txt");

        return EXIT_SUCCESS;
}
