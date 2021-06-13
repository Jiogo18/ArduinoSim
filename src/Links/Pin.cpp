#include "Pin.h"

Pin::Pin(int pinNumber) : pinNumber(pinNumber) {}

Pin::~Pin()
{
    linkToPin(nullptr); // unlink
}

int Pin::getNumber() const { return pinNumber; }

void Pin::linkToPin(Pin *p)
{
    if(pinLinked) {
        // delink
        pinLinked->pinLinked = nullptr;
    }
    pinLinked = p;
    if(pinLinked) {
        // link
        pinLinked->pinLinked = this;
    }
}

Pin *Pin::getLinkedPin()
{
    return pinLinked;
}

void Pin::setPinMode(int mode) { this->mode = mode; }

void Pin::setVoltage(double v) { voltage = std::max(std::min(v, voltageMax), voltageMin); PWMRatio = 255; }

void Pin::setPWMRatio(uint8_t value) { voltage = Pin::voltageMax; this->PWMRatio = value; }

double Pin::getVoltage() const
{
    const Pin *p = getPinForValue();
    return p->voltage * p->PWMRatio / 255;
}

uint8_t Pin::getPWMRatio() const
{
    return getPinForValue()->PWMRatio;
}

const Pin *Pin::getPinForValue() const
{
    return (mode == INPUT && pinLinked) ? pinLinked : this;
}
