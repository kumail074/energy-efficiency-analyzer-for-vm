# Energy Efficiency Analyzer for Virtual Machines

This project provides a tool to monitor and estimate the energy consumption of virtual machines (VMs). The tool collects system resource data such as CPU, memory, disk I/O, and network I/O, estimates the energy consumption based on this data, and exports the results in CSV and JSON formats. The tool supports periodic monitoring and logging of resource usage.

---

## Features

- Monitors resource usage (CPU, memory, disk I/O, network I/O) of a virtual machine (VM).
- Estimates energy consumption based on resource data.
- Logs monitoring results.
- Exports the results to CSV and JSON files.
- Customizable monitoring interval.
- Supports both Linux and VirtualBox-based virtual machines.

---

## Requirements

- **Operating System**: Linux-based OS (Ubuntu, CentOS, etc.).
- **Dependencies**:
  - `libc` (for system calls like `open`, `read`, `write`, `sleep`).
  - `time.h` (for timestamp generation).
  - `fcntl.h` (for file operations).
  - `json-c` (for JSON parsing, if not available, you'll need to implement or link to a different JSON library).
  
- **Virtualization**:
  - VirtualBox (for VM detection and monitoring).
  - The virtual machine must have VirtualBox tools installed if it's a VirtualBox-based guest.

---

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/energy-efficiency-analyzer.git
    cd energy-efficiency-analyzer
    ```

2. Install dependencies (example for Ubuntu):

    ```bash
    sudo apt-get install libjson-c-dev
    ```

3. Compile the project:

    ```bash
    make
    ```

4. Run the program:

    ```bash
    ./energy_analyzer
    ```

---

## Configuration

Before running the tool, you need to configure the program by providing necessary parameters in the `Config` structure, which can be specified via the command line or through a configuration file.

### Command-line Parameters

Here are the available parameters you can use to configure the program:

| Parameter             | Description                                                         |
|-----------------------|---------------------------------------------------------------------|
| `-c` or `--config`     | Path to the configuration file (optional). Default: `config.cfg`.   |
| `-l` or `--log`        | Path to the log file (optional). Default: `logfile.log`.            |
| `-o` or `--output`     | Path to the output file for exporting data (CSV/JSON). Default: `output.csv`. |
| `-v` or `--vm-name`    | Name of the virtual machine to monitor. Default: `VM1`.             |
| `-i` or `--interval`   | Monitoring interval in seconds (default: 60 seconds).               |

### Example Usage

```bash
./energy_analyzer -c config.cfg -l logfile.log -o output.csv -v "VM1" -i 60

