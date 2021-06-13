#include "ComponentArduino.h"

ComponentArduino::ComponentArduino() :
    Component(QPixmap(":/ressources/arduino-UNO.png").scaledToWidth(200))
{
    p0 = new Pin(D0); // RX
    p1 = new Pin(D1); // TX
    p2 = new Pin(D2);
    p3 = new Pin(D3); // ~
    p4 = new Pin(D4);
    p5 = new Pin(D5); // ~
    p6 = new Pin(D6); // ~
    p7 = new Pin(D7);

    p8 = new Pin(D8);
    p9 = new Pin(D9); // ~
    p10 = new Pin(D10); // ~
    p11 = new Pin(D11);
    p12 = new Pin(D12);
    p13 = new Pin(D13);
    pGND = new Pin(GND); // GND
    pSDA = new Pin(SDA);
    pSCL = new Pin(SCL);

    pA0 = new Pin(A0);
    pA1 = new Pin(A1);
    pA2 = new Pin(A2);
    pA3 = new Pin(A3);
    pA4 = new Pin(A4);

    p5V = new Pin(V5); // 5 V
    p33V = new Pin(V33); // 3.3 V

    setPinVoltage(pGND, 0);
    setPinVoltage(p5V, 5);
    setPinVoltage(p33V, 3);

    HE10_20 = new HE10(0x20);
    HE10_21 = new HE10(0x21);
    HE10_22 = new HE10(0x22);
    HE10_24 = new HE10(0x24);
    HE10_23 = new HE10(0x23);

    Wire = WireLib({ HE10_20, HE10_21, HE10_22, HE10_23, HE10_24 });
    Serial = SerialLib();
}

ComponentArduino::~ComponentArduino()
{
    if(isRunning() && !wait(1000)) {
        terminate();
    }

    delete p0;
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    delete p6;
    delete p7;

    delete p8;
    delete p9;
    delete p10;
    delete p11;
    delete p12;
    delete p13;
    delete pGND;
    delete pSDA;
    delete pSCL;

    delete pA0;
    delete pA1;
    delete pA2;
    delete pA3;
    delete pA4;

    delete p5V;
    delete p33V;

    delete HE10_20;
    delete HE10_21;
    delete HE10_22;
    delete HE10_24;
    delete HE10_23;
}

void ComponentArduino::stop()
{
    requestInterruption();
}

Pin *ComponentArduino::getPin(int pinNum)
{
    switch(pinNum) {
    case D0: return p0;
    case D1: return p1;
    case D2: return p2;
    case D3: return p3;
    case D4: return p4;
    case D5: return p5;
    case D6: return p6;
    case D7: return p7;

    case D8: return p8;
    case D9: return p9;
    case D10: return p10;
    case D11: return p11;
    case D12: return p12;
    case D13: return p13;

    case GND: return pGND;
    case SDA: return pSDA;
    case SCL: return pSCL;

    case A0: return pA0;
    case A1: return pA1;
    case A2: return pA2;
    case A3: return pA3;
    case A4: return pA4;

    case V5: return p5V;
    case V33: return p33V;
    }
    qFatal((QString("Unknow pin on Arduino : ") + QString::number(pinNum)).toStdString().c_str());
    return nullptr;
}

HE10 *ComponentArduino::getHE10(int adresse)
{
    switch(adresse) {
    case HE10_MOTEURS_12: return HE10_20;
    case HE10_S1: return HE10_21;
    case HE10_S2: return HE10_22;
    case HE10_E2: return HE10_23;
    case HE10_E1: return HE10_24;
    }
    qFatal((QString("Unknow HE10 on Arduino : ") + QString::number(adresse)).toStdString().c_str());
    return nullptr;
}

void ComponentArduino::setup() {}
void ComponentArduino::loop() {}

void ComponentArduino::run()
{
    msleep(100); // temps pour démarrer
    setup();
    while(!isInterruptionRequested()) {
        loop();
    }
}

void ComponentArduino::requestInterruption()
{
    QThread::requestInterruption();
    if(!wait(100)) quit();

    if(isRunning() && !wait(500)) {
        //qWarning() << "ArduinoSimThread is not finished => terminate";
        terminate();
        if(!wait(1000))
            qWarning() << "ArduinoSimThread didn't stopped";
    }
}

void ComponentArduino::pinMode(uint8_t pin, uint8_t mode)
{
    Pin *p = getPin(pin);
    if(p) {
        p->setPinMode(mode);
    }
    else {
        qWarning() << "pinMode" << pin << "doesn't exist";
    }
}

void ComponentArduino::digitalWrite(uint8_t pin, bool value)
{
    Pin *p = getPin(pin);
    if(p) {
        // DC sur HIGH (voltageMax) ou LOW (voltageMin)
        p->setVoltage(value ? Pin::voltageMax : Pin::voltageMin);
    }
    else {
        qWarning() << "digitalWrite" << pin << "doesn't exist";
    }
}

bool ComponentArduino::digitalRead(uint8_t pin)
{
    Pin *p = getPin(pin);
    if(p) {
        // DC sur HIGH (voltageMax) ou LOW (voltageMin)
        return (p->getVoltage() >= (Pin::voltageMax + Pin::voltageMin) / 2) ? HIGH : LOW;
    }
    else {
        qWarning() << "digitalWrite" << pin << "doesn't exist";
        return 0;
    }
}

void ComponentArduino::analogWrite(uint8_t pin, uint8_t value)
{
    Pin *p = getPin(pin);
    if(p) {
        // AC en PWM avec un ratio value / 255
        // (value = 0 est équivalent à du DC LOW)
        // (value = 255 est équivalent à du DC HIGH)
        p->setPWMRatio(value);
    }
    else {
        qWarning() << "analogWrite" << pin << "doesn't exist";
    }
}

int ComponentArduino::analogRead(uint8_t pin)
{
    Pin *p = getPin(pin);
    if(p) {
        // Tension efficace (0-5 V) passée sur la plage 0-1023
        return p->getVoltage() * 1023 / Pin::voltageMax;
    }
    else {
        qWarning() << "analogRead" << pin << "doesn't exist";
        return 0;
    }
}

