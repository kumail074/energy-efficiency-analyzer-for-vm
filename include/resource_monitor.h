/*** declarations for resource monitoring ***/

#ifndef RESOURCE_MONITOR_H
#define RESOURCE_MONITOR_H

typedef struct {
    char vm_name[64];
    int cpu_usage;
    int memory_usage;
    long disk_io;
    long network_io;
} ResourceData; 

int init_resource_monitor(void);
ResourceData get_resource_usage(const char *vm_name);
void close_resource_monitor(void);

#endif
