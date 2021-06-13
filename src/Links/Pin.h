#ifndef PIN_H
#define PIN_H

#include "Arduino.h"
#include "../ArduinoSimLibGlobal.h"

class ARDUINO_SIM_EXPORT Pin
{
public:
    Pin(int pinNumber);
    ~Pin();
    static constexpr const double voltageMin = 0;
    static constexpr const double voltageMax = 5;

    int getNumber() const;
    void linkToPin(Pin *p);
    Pin *getLinkedPin();

    void setPinMode(int mode);
    void setVoltage(double v);
    void setPWMRatio(uint8_t value);
    double getVoltage() const;
    uint8_t getPWMRatio() const;


private:
    int pinNumber;
    int mode;
    double voltage;
    uint8_t PWMRatio; // varie de 0 à 255
    Pin *pinLinked = nullptr;
    const Pin *getPinForValue() const;
};

#endif // PIN_H
