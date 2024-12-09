/*** declarations for energy estimation ***/

#ifndef ENERGY_ESTIMATION_H
#define ENERGY_ESTIMATION_H

typedef struct {
    double cpu_usage;
    double memory_usage;
    double disk_usage;
} ResourceData;

double estimate_energy_usage(const ResourceData *data);
void set_energy_model_parameters(double *params);

#endif
