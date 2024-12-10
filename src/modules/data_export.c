/*** Exports results to CSV or JSON ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "../../include/data_export.h"

/*typedef struct {
	char vm_name[64];
	double energy_consumed;
	int monitoring_duration;
} AnalysisData; */

int export_data_to_csv(const char *file_path, const AnalysisData *data) { 
    if(!file_path || !data) {
        fprintf(stderr, "Invalid arguments to export_data_to_csv.\n");
        return -1;
    }

    FILE *file = fopen(file_path, "w");
    if(!file) {
        perror("Failed to open CSV file");
        return -1;
    }

    fprintf(file, "Timestamp, CPU Usage, Memory Usage, Disk Usage, Energy Consumption\n");

    for(int i = 0; i < data->count; ++i) {
        fprintf(file, "%s,%.2f,%.2f,%.2f,%.2f\n",
                data->entries[i].timestamp,
                data->entries[i].cpu_usage,
                data->entries[i].memory_usage,
                data->entries[i].disk_usage,
                data->entries[i].energy_consumption);
    }
    fclose(file);
    return 0;
}

int export_data_to_json(const char *file_path, const AnalysisData *data) {
    if(!file_path || !data) {
        fprintf(stderr, "Invalid arguments to export_data_to_json.\n");
        return -1;
    }

    FILE *file = fopen(file_path, "w");
    if(!file) {
        perror("Failed to open JSON file");
        return -1;
    }

    fprintf(file, "{\n\"data\": [\n");

    for(int i = 0; i < data->count; ++i) {
        fprintf(file, " {\n");
        fprintf(file, "     \"timestamp\": \"%s\",\n", data->entries[i].timestamp);
        fprintf(file, "     \"cpu_usage\": %.2f,\n", data->entries[i].cpu_usage);
        fprintf(file, "     \"memory_usage\": %.2f,\n", data->entries[i].memory_usage);
        fprintf(file, "     \"disk_usage\": %.2f,\n", data->entries[i].disk_usage);
        fprintf(file, "     \"energy_consumption\": %.2f\n", data->entries[i].energy_consumption);
        fprintf(file, " }%s\n", (i == data->count - 1) ? "" : ",");
    }

    fprintf(file, "]\n}\n");
    fclose(file);
    return 0;
}
