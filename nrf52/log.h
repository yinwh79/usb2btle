#ifndef LOG_H
#define LOG_H

#define DEBUG 0
#if DEBUG
#define dbgPrint(...) Serial.print(__VA_ARGS__)
#define dbgPrintf(...) Serial.printf(__VA_ARGS__)
#define dbgPrintln(...) Serial.println(__VA_ARGS__)
#define dbgWrite(...) Serial.write(__VA_ARGS__)
#else
#define dbgPrint(...)
#define dbgPrintf(...)
#define dbgPrintln(...)
#define dbgWrite(...)
#endif

#endif
