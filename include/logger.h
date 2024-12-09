/*** declaration for logging ***/

#ifndef LOGGER_H
#define LOGGER_H

int init_logger(const char *log_file);
void log_message(const char *level, const char *message);
void close_logger(void);

#endif
