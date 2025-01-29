
#pragma once

#include <sys/types.h>

typedef struct {
    int   BaudRate;
    uint  Port;
    uint  Save;
    uint  Duration;
    bool  HumanTime;
} Arguments;

Arguments* parse_inputs( int, char* [] );
void print_usage();

