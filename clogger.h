#ifndef CLOGGER_H
#define CLOGGER_H

#include <stdio.h>

#define MSGMAXLENGTH 512

typedef enum log_type {
        INFO,
        DEBUG,
        WARN,
        ERROR
} log_type_t;

#if defined(NCLOG)
  #define LOG_INFO(FORMAT, ...)
  #define LOG_DEBUG(FORMAT, ...)
  #define LOG_WARNING(FORMAT, ...)
  #define LOG_ERROR(FORMAT, ...)
#else
  #define LOG_INFO(FORMAT, ...) \
        log_to_console(INFO, __FILE__, __func__, __LINE__, FORMAT, ##__VA_ARGS__);
  #define LOG_DEBUG(FORMAT, ...) \
        log_to_console(DEBUG, __FILE__, __func__, __LINE__, FORMAT, ##__VA_ARGS__);
  #define LOG_WARNING(FORMAT, ...) \
        log_to_console(WARN, __FILE__, __func__, __LINE__, FORMAT, ##__VA_ARGS__);
  #define LOG_ERROR(FORMAT, ...) \
        log_to_console(ERROR, __FILE__, __func__, __LINE__, FORMAT, ##__VA_ARGS__);
#endif /* NCLOG */

#define LOG_INFO_F(FILEPATH, FORMAT, ...) \
        log_to_file(INFO, FILEPATH, __FILE__, __func__, __LINE__, FORMAT, ##__VA_ARGS__);
#define LOG_DEBUG_F(FILEPATH, FORMAT, ...) \
        log_to_file(DEBUG, FILEPATH, __FILE__, __func__, __LINE__, FORMAT, ##__VA_ARGS__);
#define LOG_WARNING_F(FILEPATH, FORMAT, ...) \
        log_to_file(WARN, FILEPATH, __FILE__, __func__, __LINE__, FORMAT, ##__VA_ARGS__);
#define LOG_ERROR_F(FILEPATH, FORMAT, ...) \
        log_to_file(ERROR, FILEPATH, __FILE__, __func__, __LINE__, FORMAT, ##__VA_ARGS__);

void log_to_console(log_type_t type, const char *filename, const char *function,
             int line, const char *format, ...);
void log_to_file(log_type_t type, const char *filepath, const char *filename,
               const char *function, int line, const char *format, ...);

#endif /* CLOGGER_H */
