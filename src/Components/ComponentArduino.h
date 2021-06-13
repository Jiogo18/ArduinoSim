#ifndef COMPONENTARDUINO_H
#define COMPONENTARDUINO_H

#include "Component.h"
#include <QList>
#include <QThread>
#include "Wire.h"
#include "Serial.h"

class ARDUINO_SIM_EXPORT ComponentArduino : public Component, public QThread
{
public:
    enum pins {
        D0 = 0, // RX
        D1 = 1, // TX
        D2 = 2,
        D3 = 3, // ~
        D4 = 4,
        D5 = 5, // ~
        D6 = 6, // ~
        D7 = 7,

        D8 = 8,
        D9 = 9, // ~
        D10 = 10, // ~
        D11 = 11,
        D12 = 12,
        D13 = 13,
        GND = GND,
        SDA = SDA,
        SCL = SCL,

        A0 = A0,
        A1 = A1,
        A2 = A2,
        A3 = A3,
        A4 = A4,
        V5 = V5, // 5V
        V33 = V33 // 3.3V
    };
    enum HE10_NAME {
        // Carte d'extension P'O
        HE10_MOTEURS_12 = 0x20,
        HE10_S1 = 0x21,
        HE10_S2 = 0x22,
        HE10_E2 = 0x23,
        HE10_E1 = 0x24,
    };

    ComponentArduino();
    ~ComponentArduino();

    void stop();

    Pin *getPin(int pinNum) override;
    HE10 *getHE10(int adresse) override;

protected:
    WireLib Wire;
    SerialLib Serial;
    virtual void setup();
    virtual void loop();
    void run() override;
    void requestInterruption();
    void pinMode(uint8_t pin, uint8_t mode);
    void digitalWrite(uint8_t pin, bool value);
    bool digitalRead(uint8_t pin);
    void analogWrite(uint8_t pin, uint8_t value);
    int analogRead(uint8_t pin);


private:
    Pin *p0; // RX
    Pin *p1; // TX
    Pin *p2;
    Pin *p3; // ~
    Pin *p4;
    Pin *p5; // ~
    Pin *p6; // ~
    Pin *p7;

    Pin *p8;
    Pin *p9; // ~
    Pin *p10; // ~
    Pin *p11;
    Pin *p12;
    Pin *p13;
    Pin *pGND; // GND
    Pin *pSDA;
    Pin *pSCL;

    Pin *pA0;
    Pin *pA1;
    Pin *pA2;
    Pin *pA3;
    Pin *pA4;

    Pin *p5V; // 5 V
    Pin *p33V; // 3.3 V

    HE10 *HE10_20;
    HE10 *HE10_21;
    HE10 *HE10_22;
    HE10 *HE10_24;
    HE10 *HE10_23;

};


#endif // COMPONENTARDUINO_H
