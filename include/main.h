#ifndef MAIN_H
#define MAIN_H 

typedef struct {
    char config_file[256];
    char log_file[256];
    char output_file[256];
    int monitoring_interval;
} Config;

void parse_arguments(int argc, char *argv[], Config *config);
void init(Config *config);
void run_monitoring(Config *config);

#endif
