#ifndef CustomDebug_h
#include "Arduino.h"
#define CustomDebug_h
enum DebugLevel
{
    INFO,
    VERBOSE,
    WARNING,
    ERROR,
    DEBUG,
    FATAL,
    ALL,
    OFF
};
inline const char *DebugLevelToString(DebugLevel v);
void cLog(char *message, DebugLevel v=DebugLevel::INFO);
void cLog(String message, DebugLevel v=DebugLevel::INFO);
#endif