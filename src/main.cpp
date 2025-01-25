
// main.cpp

#include <iostream>
#include "InputParser.h"
#include "SerialReader.h"

int main( int argc, char* argv[] )
{
    if ( argc < 2 )
    {
        std::cerr << "Error: Missing required argument\n\n";
        print_usage();
        return 1;
    }

    const Arguments INPUTS = parse_inputs( argc, argv );

    try
    {
        SerialReader Reader(
            argv[INPUTS.Port],
            INPUTS.Duration,
            INPUTS.BaudRate
        );
        Reader.OpenPort();

        if ( INPUTS.Save == 0 )
        {
            std::cout << "Reading data from serial port: " << argv[INPUTS.Port] << std::endl;
            Reader.PrintValues();
        }
        else
        {
            std::cout
                << "Saving serial port: " << argv[INPUTS.Port] << " data in: "
                << argv[INPUTS.Save] << std::endl;

            Reader.SaveData( argv[INPUTS.Save] );
        }
    }
    catch ( const std::exception& e )
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

