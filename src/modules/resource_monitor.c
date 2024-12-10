/*** Monitors VM resource usage ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../../include/resource_monitor.h"

int init_resource_monitor(void) {
    if(access("/proc/stat", F_OK) != 0) {
    perror("Error: /proc/stat not found.");
    return -1;
    }
    if(access("proc/meminfo", F_OK) != 0) {
        perror("Error: /proc/meminfo not found.");
        return -1;
    }
    if(access("proc/net/dev", F_OK) != 0) {
        perror("Error: /proc/net/dev not found.");
        return -1;
    }

    printf("Resource monitoring initialized successfully.\n");
    return 0;
}
    

ResourceData get_resource_usage(const char *vm_name) {
    ResourceData data;
    memset(&data, 0 , sizeof(data));
    strncpy(data.vm_name, vm_name, sizeof(data.vm_name) - 1);

    FILE *cpu_file = fopen("/proc/stat", "r");
    if(cpu_file) {
        char buffer[256];
        if(fgets(buffer, sizeof(buffer), cpu_file)) {
            long user, nice, system, idle;
            sscanf(buffer, "cpu %ld %ld %ld %ld", &user, &nice, &system, &idle);
            data.cpu_usage = (int)((user + nice + system) * 100 / (user + nice + system + idle));
        }
        fclose(cpu_file);
    } else {
        perror("Failed to read /proc/stat for CPU usage");
    }

    FILE *mem_file = fopen("/proc/meminfo", "r");
    if(mem_file) {
        char key[64];
        long *value;
        long total_memory = 0, available_memory = 0;

        while(fscanf(mem_file, "%63s %ld kB\n", key, value) == 2) {
            if(strcmp(key, "MemTotal:") == 0) {
                total_memory = *value;
                break;
            }
        }
        if(total_memory > 0) {
            data.memory_usage = (int)((total_memory - available_memory) * 100 / total_memory);
        }
        fclose(mem_file);
    } else {
        perror("Failed to read /proc/meminfo for memory usage");
    }

    FILE *disk_file = fopen("/proc/diskstats", "r");
    if(disk_file) {
        char buffer[256], disk_name[32];
        long sectors_read, sectors_written;

        while(fgets(buffer, sizeof(buffer), disk_file)) {
            if(sscanf(buffer, "%*d %*d %31s %*s %*d %*d %*d %ld %*d %*d %*d %ld", disk_name, &sectors_read, &sectors_written) == 3) {
                data.disk_io += sectors_read + sectors_written;
            }
        }
        fclose(disk_file);
    } else {
        perror("Failed to read /proc/diskstats for disk I/O");
    }

    FILE *net_file = fopen("/proc/net/dev", "r");
    if(net_file) {
        char interface[32];
        long bytes_received, bytes_sent;
        char buffer[256];

        fgets(buffer, sizeof(buffer), net_file);
        fgets(buffer, sizeof(buffer), net_file);

        while(fgets(buffer, sizeof(buffer), net_file)) {
            if(sscanf(buffer, "%31s %ld %*d %*d %*d %*d %*d %*d %ld", interface, &bytes_received, &bytes_sent) == 3) {
                data.network_io += bytes_received + bytes_sent;
            }
        }
        fclose(net_file);
    } else {
        perror("Failed to read /proc/net/dev for network I/O");
    }
    return data;
}



//void close_resource_monitor(void);

