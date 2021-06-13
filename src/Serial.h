#ifndef SERIALLIB_H
#define SERIALLIB_H

#include "ArduinoSimLibGlobal.h"
#include <string>
#include <iostream>

class ARDUINO_SIM_EXPORT SerialLib
{
public:
    SerialLib();
    void begin(int adresse);

    static void println(const char* line);
    static void println(int v);
    static void println(double v);
    static void println(bool v);

    static void print(const char* line);
    static void print(int v);
    static void print(double v);
    static void print(bool v);

    static int charToOem(int c);
    static std::string charsToOem(const char* line);

private:
    int adresse;
};

#endif // SERIALLIB_H
