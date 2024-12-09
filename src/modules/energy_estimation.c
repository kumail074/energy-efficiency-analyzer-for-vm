/*** Estimates energy consumption per VM ***/

#include <stdio.h>
#include <stdlib.h>
#include "resource_monitor.h"

typedef struct {
    double cpu_power;
    double mem_power;
    doub;e io_power;
} EnergyModel;

static EnergyModel energy_model = {1.5, 0.8, 0.5};

double estimate_energy_usage(const struct ResourceData *data);
void set_energy_model_parameters(double *params);

double estimate_energy_usage(const struct ResourceData *data) {
    if(!data) {
        fprintf(stderr, "Resource data is NULL.\n");
        return -1.0;
    }
    double energy = (data->cpu_usage * energy_model.cpu_power) + (data->memory_usage * energy_model.mem_power) + (data->io_usage * energy_model.io_power);

    return energy;
}

void set_energy_model_parameters(double *params) {
    if(!params) {
        fprintf(stderr, "Parameters array is NULL.\n");
        return;
    }

    energy_model.cpu_power = params[0];
    energy_model.mem_power = params[1];
    energy_model.io_power = params[2];

    printf("Energy model parameters updated:\n");
    printf("CPU Power: %.2f W\n", energy_model.cpu_power);
    printf("Memory Power: %.2f W\n", energy_model.mem_power);
    printf("I/O Power: %.2f W\n", energy_model.io_power);
}
