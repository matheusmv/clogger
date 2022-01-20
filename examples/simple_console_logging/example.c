#include <stdio.h>
#include <stdlib.h>

#include "../../clogger.h"

void
log_with_colors()
{
        clogger_colored_console(ACTIVE);
        LOG_INFO("random %s message", "info");
        LOG_DEBUG("random %s message", "debug");
        LOG_WARNING("random %s message", "warning");
        LOG_ERROR("random %s message", "error");
}

void
log_without_colors()
{
        clogger_colored_console(INACTIVE);
        LOG_INFO("random %s message", "info");
        LOG_DEBUG("random %s message", "debug");
        LOG_WARNING("random %s message", "warning");
        LOG_ERROR("random %s message", "error");
}

int main(void)
{
        log_with_colors();
        log_without_colors();

        return EXIT_SUCCESS;
}
