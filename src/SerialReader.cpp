
// SerialReader.cpp

#include "SerialReader.h"
#include <fstream>
#include <chrono>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <ostream>
#include <stdexcept>

#define time std::chrono


//- PRIVATE METHODS --------------------------------------------------------------------------------

void SerialReader::configurePort()
{
    struct termios lTTY;

    if ( tcgetattr(fFileDescriptor, &lTTY) != 0)
    {
        throw std::runtime_error( "Failed to get serial port attributes" );
    }

    cfsetospeed( &lTTY, fBaudRate );
    cfsetispeed( &lTTY, fBaudRate );

    lTTY.c_cflag = ( lTTY.c_cflag & ~CSIZE ) | CS8; // 8-bit characters
    lTTY.c_iflag &= ~IGNBRK;                        // disable break processing
    lTTY.c_lflag = 0;                               // no echo, no canonical processing
    lTTY.c_oflag = 0;                               // no remapping, no delays
    lTTY.c_cc[VMIN] = 1;                            // read at least 1 character
    lTTY.c_cc[VTIME] = 0;                           // no timeout

    lTTY.c_iflag &= ~( IXON | IXOFF | IXANY );      // disable flow control
    lTTY.c_cflag |= ( CLOCAL | CREAD );             // enable reading
    lTTY.c_cflag &= ~( PARENB | PARODD );           // disable parity
    lTTY.c_cflag &= ~CSTOPB;                        // 1 stop bit
    lTTY.c_cflag &= ~CRTSCTS;                       // no hardware flow control

    if ( tcsetattr(fFileDescriptor, TCSANOW, &lTTY) != 0 )
    {
        throw std::runtime_error( "Failed to set serial port attributes" );
    }
}


void SerialReader::currentTime( std::ostream& aStream )
{
    // only set color on macOS and Linux
    #if !defined(_WIN32) && !defined(_WIN64)
        std::cout << "\033[33m";
    #endif

    if ( fHumanTime )
    {
        const auto NOW = time::system_clock::now();
        const auto NOW_C = time::system_clock::to_time_t( NOW );
        const std::tm LOCAL_TM = *std::localtime( &NOW_C );
        auto milliseconds = time::duration_cast<time::milliseconds>
            ( NOW.time_since_epoch() ) % 1000;

        aStream
            << std::setw(2) << std::setfill('0') << LOCAL_TM.tm_hour << ":"
            << std::setw(2) << std::setfill('0') << LOCAL_TM.tm_min << ":"
            << std::setw(2) << std::setfill('0') << LOCAL_TM.tm_sec << "."
            << std::setw(3) << std::setfill('0') << milliseconds.count()
            << " : ";
    }
    else
    {
        aStream
            << time::duration_cast<time::microseconds>(
                time::high_resolution_clock::now().time_since_epoch()).count()
            << "µs : ";
    }

    #if !defined(_WIN32) && !defined(_WIN64)
        std::cout << "\033[36m";
    #endif

}


void SerialReader::readValues( std::ostream& aStream )
{
    auto lStartTime = time::steady_clock::now();

    do
    {
        char lBuffer[1];
        int lSerialRead = read( fFileDescriptor, lBuffer, 1 );

        if ( lSerialRead <  0 ) throw std::runtime_error( "Error reading from serial port" );
        if ( lSerialRead == 0 ) continue;

        aStream << lBuffer[0];

        if ( lBuffer[0] == '\n' ) currentTime( aStream );
    }
    while
    (
        fDuration == 0 ||
        time::steady_clock::now() - lStartTime < time::seconds(fDuration) 
    );
}


//- PUBLIC METHODS ---------------------------------------------------------------------------------

void SerialReader::OpenPort()
{
    fFileDescriptor = open( fPort.c_str(), O_RDWR | O_NOCTTY | O_SYNC );
    if ( fFileDescriptor == -1 )
    {
        throw std::runtime_error( "Failed to open serial port: " + fPort );
    }
    configurePort();
}


void SerialReader::ClosePort()
{
    if ( fFileDescriptor != -1 )
    {
        close( fFileDescriptor );
    }
}


void SerialReader::PrintValues()
{
    readValues( std::cout );
}


void SerialReader::SaveData( char* aFileName )
{
    std::ofstream lFileStream( aFileName );
    if ( !lFileStream.is_open() )
    {
        std::cerr << "Error opening file: " << aFileName << std::endl;
        return;
    }

    if ( fDuration == 0 ) { fDuration = 60; }

    readValues( lFileStream );

    lFileStream.close();
}

