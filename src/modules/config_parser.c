/*** Parses user-defined configuration files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config_parser.h"
#include "main.h"

int parse_config(const char *config_file, Config *config);
void print_config(const char *config_file, Config *config);

int parse_config(const char *config_file, Config *config) {
    if(!config_file || !config) {
        fprintf(stderr, "Invalid arguments to parse_config.\b");
        return -1;
    }

    FILE *file = fopen(config_file, "r");
    if(!file) {
        perror("Failed to open configuration file");
        return -1;
    }

    char line[256];
    while(fgets(line, sizeof(line), file)) {
        char key[128], value[128];
        if(line[0] == '#' || line[0] == '\n') {
            continue;
        }

        if(sscanf(line, "%127[^=]=%127s", key, value) == 2) {
            if(strcmp(key, "config_file") == 0) {
                strncpy(config->config_file, value, sizeof(config->config_file) - 1);
            } else if(strcmp(key, "log_file") == 0) {
                strncpy(config->log_file, value, sizeof(config->log_file) - 1);
            } else if(strcmp(key, "output_file") == 0) {
                strncpy(config->output_file, value, sizeof(config->output_file) - 1);
            } else if(strcmp(key, "monitoring_interval") == 0) {
                config->monitoring_interval = atoi(value);
            } else {
                fprintf(stderr, "Unknown configuration key: %s\n", key);
            }
        }
    }
    fclose(file);
    return 0;
}

void print_config(const Config *config) {
    if(!config) {
        fprintf(stderr, "Invalid Config pointer.\n");
        return;
    }

    printf("Configuration: \n");
    printf("    Config File: %s\n", config->config_file);
    printf("    Log File: %s\n", config->log_file);
    printf("    Output File: %s\n", config->output_file);
    printf("    Monitoring Interval: %d seconds\n", config->monitoring_interval);
}



