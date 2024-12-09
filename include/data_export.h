/*** declarations for data export ***/

#ifndef DATA_EXPORT_H
#define DATA_EXPORT_H

typedef struct {
    char timestamp[20];
    double cpu_usage;
    double memory_usage;
    double disk_usage;
    double energy_consumption;
} DataEntry;

typedef struct {
    DataEntry entries[100];
    int count;
} AnalysisData;

int export_data_to_csv(const char *file_path, const AnalysisData *data);
int export_data_to_json(const char *file_path, const AnalysisData *data);

#endif
