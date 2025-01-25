
#pragma once

#include <string>
#include <termios.h>

using std::string;

class SerialReader {
private:
    int fBaudRate, fFileDescriptor, fDuration;
    bool fHumanTime;
    string fPort;

    void configurePort();
    void currentTime( std::ostream& );
    void readValues( std::ostream& );

public:
    SerialReader( const string& Port, int Duration, int BaudRate, bool HumanTime ) :
        fPort( Port ),
        fDuration( Duration ),
        fBaudRate( BaudRate ),
        fHumanTime( HumanTime ),
        fFileDescriptor( -1 )
    { }

    ~SerialReader() { ClosePort(); }

    void OpenPort();
    void ClosePort();
    void PrintValues();
    void SaveData( char* );
};

