#ifndef MAIN_H
#define MAIN_H

#include "resource_monitor.h"
#include "energy_estimation.h"
#include "energy_monitor.h"
#include "logger.h"
#include "data_export.h"

typedef struct {
    char config_file[256];
    char log_file[256];
    char output_file[256];
    int monitoring_interval;
    char vm_name[64];
} Config;

void parse_arguments(int argc, char *argv[], Config *config);
void init(Config *config);
void run_monitoring(Config *config);

#endif
