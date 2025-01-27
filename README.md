# SerialMonitor

SerialMonitor is a continuation and fork of a custom tool I developed for
[Haemograph Pyt. Ltd.](https://github.com/Haemograph-Rheometer/) to monitor the firmware I worked
on. It has now been improved to serve as a more general tool for reading from the Serial Monitor and
recording logs.



## Usage

![screenshot](./.screenshot.png)

```
Usage:
  $ smonitor [port] [baud rate] {file.txt} -d {duration} --human-time

Options:
  port              Port to connect to (required)
  baud              Baud rate for serial communication (e.g., 9600, 19200)
  duration          Time in seconds for serial read. 0 for forever. (default 60)
  file              Path to the file.txt where logs will be saved

Flags:
  --human-time      Instead of µs, get time in hh:mm:ss.SSS

Example:
  $ monitor /dev/tty.usbmodem101 115200 -d 600 -o ./data.txt
  This command saves logs for 10 minutes in data.txt

  $ monitor /dev/tty.usbmodem101 9600 -d 0 --human-time
  This command prints serial data indefinitely with time in hh:mm:ss.SSS.

Notes:
  - Ensure the specified port is correct and accessible.
  - The duration is specified in seconds; use 0 for continuous logging, but it
    cannot be set to 0 when writing to a file.
  - The output file will be created if it does not exist, or overwritten if it does.
  - Logs are written to the file whenever a filename is specified.
  - Use the --ignore-values flag if you only want to log the timestamps.
```



## Installation Instructions

### macOS - Apple Silicon

#### 1. Download the Latest Binary
Obtain the latest binary from the [releases](https://github.com/karshPrime/smonitor/releases).

#### 2. Add to Local Path
Move the binary to your local path:
```sh
$ mv ~/Downloads/smonitor_macOS_arm64 /usr/local/bin/smonitor
```

#### 3. Reload Your Shell
To ensure the changes take effect, reload your shell.



### Other Platforms ( Windows / GNU/Linux / Intel macOS )

#### 1. Prerequisites
Ensure you have the following installed:
* [cmake](https://cmake.org/download/)
* C compiler (e.g., GCC, Clang)

#### 2. Compile the Source Code
Run the following command to compile the source:

```sh
$ cmake -S . -B build && cmake --build build
```

#### 3. Add to Local Path
```sh
$ mv ./build/bin/smonitor /usr/local/bin/smonitor
```

#### 4. Reload Your Shell
To ensure the changes take effect, reload your shell.

