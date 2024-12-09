/*** declarations for configuration setup ***/

#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include "main.h"

int parse_config(const char *config_file, Config *config);
void print_config(const char *config_file, Config *config);

#endif
