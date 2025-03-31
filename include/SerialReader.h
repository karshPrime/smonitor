
#pragma once

#include <string>
#include <termios.h>

using std::string;

#if !defined(_WIN32) && !defined(_WIN64)
    #define TERM_RED     "\033[31m" <<
    #define TERM_BLUE    "\033[34m" <<
    #define TERM_RESET   "\033[0m"  <<

    #define TERM_COLOR_TIME_SET    std::cout << "\033[33m";
    #define TERM_COLOR_VALUE_SET   std::cout << "\033[36m";
#else
    #define TERM_RED     ""  <<
    #define TERM_RESET   ""  <<
    #define TERM_RESET   ""  <<

    #define TERM_COLOR_TIME_SET
    #define TERM_COLOR_VALUE_SET
#endif

class SerialReader {
private:
    int fBaudRate, fFileDescriptor, fDuration;
    bool fHumanTime;
    string fPort;

    void configurePort();
    void currentTime( std::ostream& );
    void readValues( bool, std::ostream& );

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
    void PrintValues( bool );
    void SaveData( bool, char* );
};

