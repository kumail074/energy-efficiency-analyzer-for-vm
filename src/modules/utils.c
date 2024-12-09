/*** General utility functions ***/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "utils.h"

char *get_current_timestamp(void);
void handle_error(const char *message);

char *get_current_timestamp(void) {
    static char timestamp[20];
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);

    if(!local_time) {
        fprintf(stderr, "Failed to get local time.\n");
        return NULL;
    }

    if(strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", local_time) == 0) {
        fprintf(stderr, "Failed to format timestamp.\n");
        return NULL;
    }
    return timestamp;
}

void handle_error(const char *message) {
    if(!message) {
        fprintf(stderr, "unknown error occured.\n");
    } else {
        fprintf(stderr, "Error: %s\n", message);
    }
    exit(EXIT_FAILURE);
}
