#ifndef CustomDebug_h
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
inline const char *DebugLevelToString(DebugLevel v)
{
    switch (v)
    {
    case DebugLevel::INFO:
        return "INFO";
    case DebugLevel::VERBOSE:
        return "VERBOSE";
    case DebugLevel::WARNING:
        return "WARNING";
    case DebugLevel::ERROR:
        return "ERROR";
    case DebugLevel::DEBUG:
        return "DEBUG";
    case DebugLevel::FATAL:
        return "FATAL";
    default:
        return "[Unknown DebugLevel]";
    }
}
void cLog(char *message, DebugLevel v=DebugLevel::INFO)
{
    String str = "";
    str += DebugLevelToString(v);
    str += " - ";
    str += message;
    Serial.println(str);
    
}
#endif