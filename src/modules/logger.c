/*** Handles loggin and output ***/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "../../include/logger.h"

static FILE *log_file_ptr = NULL;

int init_logger(const char *log_file) {
    if(!log_file) {
        fprintf(stderr, "Log file path is NULL.\n");
        return -1;
    }

    log_file_ptr = fopen(log_file, "a");

    log_message("INFO", "Logger initialized.");
    return 0;
}

void log_message(const char *level, const char *message, ...) {
    if(!log_file_ptr) {
        fprintf(stderr, "Logger not initialized.\n");
        return;
    }
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local_time);

   fprintf(log_file_ptr, "[%s] [%s] ", timestamp, level);

   va_list args;
   va_start(args, message);
   vfprintf(log_file_ptr, message, args);
   va_end(args);

   fprintf(log_file_ptr, "\n");
   fflush(log_file_ptr);
}

void close_logger(void) {
    if(log_file_ptr) {
        log_message("INFO", "Logger shutting down.");
        fclose(log_file_ptr);
        log_file_ptr = NULL;
    }
}
