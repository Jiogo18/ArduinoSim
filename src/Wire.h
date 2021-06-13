#ifndef WIRE_H
#define WIRE_H

#include "Links/HE10.h"
#include <QList>

class ARDUINO_SIM_EXPORT WireLib
{
public:
    WireLib();
    WireLib(QList<HE10*> he10s);
    void beginTransmission(int adresse);
    void begin(int adresse);
    void write(int data);
    void endTransmission();

private:
    HE10 *getHE10(int adresse);
    HE10 *he10Transmission;
    int dataTransmission;
    QList<HE10*> he10s;

};

#endif // WIRE_H
