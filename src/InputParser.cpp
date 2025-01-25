
// input_parser.cpp

#include <iostream>
#include "InputParser.h"


//- External Calls ---------------------------------------------------------------------------------

Arguments parse_inputs( int, char* [] )
{
    Arguments Result;

    return Result;
}

void print_usage()
{
    std::cout
        << "Usage:\n"
        << "  monitor [port] [baud] -d {duration} -o {file}\n\n"

        << "Options:\n"
        << "  port              Port to connect to (required)\n"
        << "  baud              Baud rate for serial communication (e.g., 9600, 19200)\n"
        << "  duration          Time in seconds for serial read. 0 for forever. (default 60)\n"
        << "  file              Path to the output file where logs will be saved\n\n"

        << "Example:\n"
        << "  $ monitor /dev/tty.usbmodem101 115200 -d 600 -o ./data.txt\n"
        << "  This command saves logs for 10 minutes in data.txt\n\n"

        << "  $ monitor /dev/tty.usbmodem101 9600 -d 0\n"
        << "  This command prints timestamps indefinitely.\n\n"

        << "Notes:\n"
        << "  - Ensure the specified port is correct and accessible.\n"
        << "  - The duration is specified in seconds; use 0 for continuous logging, but it\n"
        << "    cannot be set to 0 when writing to a file.\n"
        << "  - The output file will be created if it does not exist, or overwritten if it does.\n"
        << "  - Logs are written to the file whenever a filename is specified.\n"
        << "  - Use the --ignore-values flag if you only want to log the timestamps.\n";
}

