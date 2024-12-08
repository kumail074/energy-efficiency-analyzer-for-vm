/*** Collects energy data using RAPL or '/sys/class' ***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int initialize_energy_monitor(void);
double get_energy_consumption(void);
void close_energy_monitor(void);
