#define _DEFAULT_SOURCE
#define _GNU_SOURCE
#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <termios.h>
#include <ctype.h>
#include <getopt.h>

#include "energy_monitor.h"
#include "energy_estimation.h"
#include "config_parser.h"
#include "data_export.h"
#include "logger.h"
#include "resource_monitor.h"
#include "utils.h"

typedef struct {
	char config_file[256];
	char lof_file[256];
	char output_file[256];
	int monitoring_interval;
} Config;

void parse_arguments(int argc, char *argv[], Config *config) {
	strcpy(config->config_file, "config.cfg");
	strcpy(config->log_file, "monitor.cfg");
	strcpy(config->output_file, "output.csv");
	config->monitoring_interval = 5;

	int opt;
	while((opt = getopt(argc, argv, "c:l:o:i:")) != -1) {
		switch(opt) {
			case 'c':
				strcpy(config->config_file, optarg);
				break;
			case 'l':
				strcpy(config->log_file, optarg);
				break;
			case 'o':
				strcpy(config->output_file, optarg);
				break;
			case 'i':
				config->monitoring_interval = atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s [-c config_file] [-l log_file] [-o output_file] [-i intercal]\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
}

void init(Config **config) {
	if(init_logger(config->log_file) != 0) {
		fprintf(stderr, "Failed to initialize logger.\n");
		exit(EXIT_FAILURE);
	}

	if(initialize_energy_monitor() != 0) {
		fprintf(stderr, "Failed to initialize energy monitor.\n");
		exit(EXIT_FAILURE);
	}
	
	if(init_resource_monitor() != 0) {
		fprintf(stderr, "Failed to initialize resource monitor.\n");
		exit(EXIT_FAILURE);
	}

	if(parse_config(config->config_file, config) != 0){
		fprintf(stderr, "Failed to parse config file: %s\n", config->config_file);
	}
}

void run_monitoring(Config *config) {
	log_message("INFO", "Starting monitoring process...");

	while(1) {
		struct ResourceData resource_data = get_resource_usage("your vm");
		double estimated_energy = estimated_energy_usage(&resource_data);

		char log_msg[256];
		snprintf(log_msg, sizeof(log_msg), "Estimated Energy Consumption: %.6f Joules", estimated_energy);
		export_data_to_csv(config->output_file, &resource_data);
		export_data_to_json(config->output_file, &resource_data);
		sleep(config->monitoring_interval);
	}
}


int main(int argc, char *argv[]) {
	Config config;

	parse_arguments(argc, argv, &config);
	init(&config);
	run_monitoring(&config);
	return 0;
}
