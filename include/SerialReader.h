
#pragma once

#include <cstdint>
#include <string>
#include <termios.h>

using std::string;

class SerialReader {
private:
    int fBaudRate, fFileDescriptor, fDuration;
    string fPort;

    void configurePort();
    void currentTime( std::ostream& );
    void readValues( std::ostream& );

public:
    SerialReader( const string& Port, int Duration, int BaudRate ) :
        fPort( Port ),
        fDuration( Duration ),
        fBaudRate( BaudRate ),
        fFileDescriptor( -1 )
    { }

    ~SerialReader() { ClosePort(); }

    void OpenPort();
    void ClosePort();
    void PrintValues();
    void SaveData( char* );
};

