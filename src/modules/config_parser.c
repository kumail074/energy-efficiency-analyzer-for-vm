/*** Parses user-defined configuration files ***/

#include <stdio.h>
#include <stdlib.h>

int parse_config(const char *config_file, struct Config *config);
void print_config(const char *config_file, struct Config *config);

