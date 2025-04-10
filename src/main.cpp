
// main.cpp

#include <iostream>
#include <stdlib.h>

#include "InputParser.h"
#include "SerialReader.h"

int main( int argc, char* argv[] )
{
    if ( argc < 2 )
    {
        std::cerr << "Error: Missing required argument\n";
        print_usage();
        return 1;
    }

    if ( input_help( argv[1] ) )
    {
        std::cout << "SerialMonitor, a simple lightweight tool to read and store serial data\n";
        print_usage();
        return 0;
    }

    const Arguments* INPUTS = parse_inputs( argc, argv );

    try
    {
        SerialReader Reader(
            argv[INPUTS->Port],
            INPUTS->Duration,
            INPUTS->BaudRate,
            INPUTS->HumanTime
        );
        Reader.OpenPort();

        if ( INPUTS->Save == 0 )
        {
            std::cout
                << TERM_RED  "Reading data from serial port: "
                << TERM_BLUE  argv[INPUTS->Port] << std::endl;

            TERM_COLOR_VALUE_SET

            Reader.PrintValues( INPUTS->NoTime );
        }
        else
        {
            std::cout
                << TERM_RED   "\nReading data from "
                << TERM_BLUE  argv[INPUTS->Port]
                << TERM_RED   " for "
                << TERM_BLUE  INPUTS->Duration
                << TERM_RED   " seconds and saving the read data to "
                << TERM_BLUE  argv[INPUTS->Save]
                << std::endl;

            TERM_COLOR_VALUE_SET

            Reader.SaveData( INPUTS->NoTime, argv[INPUTS->Save] );
        }
    }
    catch ( const std::exception& e )
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    free( (void*)INPUTS );

    return 0;
}

