/*** Monitors VM resource usage ***/

#include <stdio.h>

int init_resource_monitor(void);
struct ResourceData get_resource_usage(const char *vm_name);
void close_resource_monitor(void);

typedef struct {
	char vm_name[64];
	int cpu_usage;
	int memory_usage;
	long disk_io;
	long network_io;
} ResourceData;
