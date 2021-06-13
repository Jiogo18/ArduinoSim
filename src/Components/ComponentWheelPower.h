#ifndef COMPONENTWHEELPOWER_H
#define COMPONENTWHEELPOWER_H

#include "Component.h"
#include "Links/HE10.h"

class ARDUINO_SIM_EXPORT ComponentWheelPower : public Component, public QObject
{
public:
    enum pins {
        V5 = V5,
        GND = GND,
        WA_1 = 1,
        WA_2 = 2,
        WB_1 = 3,
        WB_2 = 4,

        // INPUT
        ENA = 5,
        ENB = 6
    };
    // HE10 : 0x0

    ComponentWheelPower();
    ~ComponentWheelPower();
    Pin *getPin(int pinNum) override;
    HE10 *getHE10(int adresse) override;

private slots:
    void onHE10Data(int data);

private:
    Pin *p5V;
    Pin *pGND;
    // OUPTUT :
    Pin *pWA_1;
    Pin *pWA_2;
    Pin *pWB_1;
    Pin *pWB_2;
    // INPUT :
    Pin *pENA;
    Pin *pENB;

    HE10 *he10;

};

#endif // COMPONENTWHEELPOWER_H
