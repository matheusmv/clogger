#include <stdio.h>
#include <stdlib.h>

#include "../../clogger.h"

int main(void)
{
        /* -DLCOLOR */

        LOG_INFO("random %s message", "info");
        LOG_DEBUG("random %s message", "debug");
        LOG_WARNING("random %s message", "warning");
        LOG_ERROR("random %s message", "error");

        return EXIT_SUCCESS;
}
