/*** declaration for energy data collection ***/

#ifndef ENERGY_MONITOR_H
#define ENERGY_MONITOR_H

int initialize_energy_monitor(void);
double get_energy_consumption(void);
void close_energy_monitor(void);

#endif
