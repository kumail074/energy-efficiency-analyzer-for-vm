/*** Monitors VM resource usage ***/

#include <stdio.h>

int init(void);
struct ResourceData get_resource_usage(const char *vm_name);
void close_resource_monitor(void);
