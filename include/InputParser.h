
#pragma once

#include <sys/types.h>


typedef struct {
    int   BaudRate;
    uint  Port;
    uint  Save;
    uint  Duration;
    bool  HumanTime;
} Arguments;

Arguments parse_inputs( int, char* [] );
void print_usage();


#if !defined(_WIN32) && !defined(_WIN64)
    #define TERM_RED     "\033[31m" <<
    #define TERM_BLUE    "\033[34m" <<
    #define TERM_RESET   "\033[0m"  <<
#else
    #define TERM_RED     ""  <<
    #define TERM_RESET   ""  <<
    #define TERM_RESET   ""  <<
#endif

