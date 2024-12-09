/*** Collects energy data using RAPL or '/sys/class' ***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define ENERGY_FILE "/sys/class/powercap/intel-rapl:0/energy_uj"

static int energy_fd = -1;

int initialize_energy_monitor(void);
double get_energy_consumption(void);
void close_energy_monitor(void);

int initialize_energy_monitor(void) {
    energy_fd = open(ENERGY_FILE. O_RDONLY);
    if(energy_fd < 0) {
        perror("Failed to open energy monitoring file");
        return -1;
    }
    return 0;
}

double get_energy_consumption(void) {
    if(energy_fd < 0) {
        fprintf(stderr, "Energy monitor is not initialized.\n");
        return -1.0;
    }
    char buffer[32];
    lseek(energy_fd, 0, SEEK_SET);
    ssize_t bytes_read = read(energy_fd, buffer, sizeof(buffer) - 1);
    if(bytes_read < 0) {
        perror("Failed to read energy data");
        return -1.0;
    }

    buffer[bytes_read] = '\0';
    unsigned long long energy_uj = strtoull(buffer, NULL, 10);

    return energy_uj / 1e6;
}

void close_energy_monitor(void) {
    if(energy_fd >= 0) {
        close(energy_fd);
        energy_fd = -1;
    }
}
