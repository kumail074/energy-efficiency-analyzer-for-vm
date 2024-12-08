/*** Handles loggin and output ***/

#include <stdio.h>

int init_logger(const char *log_file);
void log_message(const char *level, const char *message);
void close_logger(void);
