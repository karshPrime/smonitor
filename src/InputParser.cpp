
// input_parser.cpp

#include <iostream>
#include "InputParser.h"


//- External Calls ---------------------------------------------------------------------------------

Arguments parse_inputs( int argc, char* argv[] )
{
    Arguments Result = {
        .BaudRate  = 9600,
        .Port      = 1,
        .Save      = 0,
        .Duration  = 60,
        .HumanTime = false,
    };

    std::string port_head = "/dev/";

    for ( int i = 0; i < argc; i++ )
    {
        if (strncmp(argv[i], port_head.c_str(), port_head.length()) == 0)
        {
            Result.Port = i;
        }
        else if ( strstr(argv[i], ".txt") != nullptr )
        {
            Result.Save = i;
        }
        else if ( strcmp( argv[i], "--human-time" ) == 0 )
        {
            Result.HumanTime = true;
        }
        else if ( isdigit( argv[i][0] ) && atoi( argv[i] ) > 0 )
        {
            Result.BaudRate = atoi( argv[i] );
        }
        else if ( strcmp( argv[i], "-d" ) == 0 )
        {
            if ( i+1 < argc && isdigit( argv[i+1][0] ) && atoi( argv[i+1] ) > 0 )
            {
                Result.Duration = atoi( argv[i+1] );
                i++;
            }
            else
            {
                std::cerr << "Error: Invalid duration.\n";
            }
        }
    }

    return Result;
}

void print_usage()
{
    std::cout
        << "\nUsage:\n"
        << "  monitor [port] [baud] {file.txt} -d {duration}\n"

        << "\nOptions:\n"
        << "  port              Port to connect to (required)\n"
        << "  baud              Baud rate for serial communication (e.g., 9600, 19200)\n"
        << "  duration          Time in seconds for serial read. 0 for forever. (default 60)\n"
        << "  file              Path to the file.txt where logs will be saved\n"

        << "\nFlags:\n"
        << "  --human-time      Instead of µs, get time in hh:mm:ss.SSS\n"

        << "\nExample:\n"
        << "  $ monitor /dev/tty.usbmodem101 115200 -d 600 -o ./data.txt\n"
        << "  This command saves logs for 10 minutes in data.txt\n"

        << "  $ monitor /dev/tty.usbmodem101 9600 -d 0 --human-time\n"
        << "  This command prints serial data indefinitely with time in hh:mm:ss.SSS.\n"

        << "\nNotes:\n"
        << "  - Ensure the specified port is correct and accessible.\n"
        << "  - The duration is specified in seconds; use 0 for continuous logging, but it\n"
        << "    cannot be set to 0 when writing to a file.\n"
        << "  - The output file will be created if it does not exist, or overwritten if it does.\n"
        << "  - Logs are written to the file whenever a filename is specified.\n"
        << "  - Use the --ignore-values flag if you only want to log the timestamps.\n";
}

