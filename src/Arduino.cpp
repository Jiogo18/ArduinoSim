#include "Arduino.h"
#include <time.h>
#include <chrono>
#include <thread>
#include <qglobal.h>

unsigned long int millis()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
unsigned long int micros()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
unsigned long int micros64()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}
void delay(long ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
void delayMicroseconds(int us)
{
    std::this_thread::sleep_for(std::chrono::microseconds(us));
}
