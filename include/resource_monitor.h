/*** declarations for resource monitoring ***/

#ifndef RESOURCE_MONITOR_H
#define RESOURCE_MONITOR_H

/*typedef struct {
    double cpu_usage;
    double memory_usage;
    double disk_usage;
} ResourceData; */

int init_resource_monitor(void);
ResourceData get_resource_usage(const char *vm_name);
void close_resource_monitor(void);

#endif
