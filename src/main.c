#define _DEFAULT_SOURCE
#define _GNU_SOURCE
#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdarg.h>
#include <termios.h>
#include <ctype.h>

#include "energy_monitor.h"
#include "energy_estimation.h"
#include "config_parser.h"
#include "data_export.h"
#include "logger.h"
#include "resource_monitor.h"
#include "utils.h"

void parse_arguments(int argc, char *argv[], Config *config);
void init();
void run_monitoring(Config *config);

int main(int argc, char *argv[]) {

	return 0;
}
