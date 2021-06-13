#include "ComponentWheelPower.h"

ComponentWheelPower::ComponentWheelPower() : Component(QPixmap()), QObject()
{
    p5V = new Pin(V5);
    pGND = new Pin(GND);
    setPinVoltage(p5V, 5);
    setPinVoltage(pGND, 0);

    pWA_1 = new Pin(WA_1);
    pWA_2 = new Pin(WA_2);
    pWB_1 = new Pin(WB_1);
    pWB_2 = new Pin(WB_2);
    setPinVoltage(pWA_1, 0);
    setPinVoltage(pWA_2, 0);
    setPinVoltage(pWB_1, 0);
    setPinVoltage(pWB_2, 0);

    pENA = new Pin(ENA);
    pENB = new Pin(ENB);
    pENA->setPinMode(INPUT);
    pENB->setPinMode(INPUT);

    he10 = new HE10(0);
    connect(he10, &HE10::onData, this, &ComponentWheelPower::onHE10Data);
}

ComponentWheelPower::~ComponentWheelPower()
{
    delete p5V;
    delete pGND;
    delete pWA_1;
    delete pWA_2;
    delete pWB_1;
    delete pWB_2;
    delete pENA;
    delete pENB;
    delete he10;
}

Pin *ComponentWheelPower::getPin(int pinNum)
{
    switch(pinNum) {
    case V5: return p5V;
    case GND: return pGND;
    case WA_1: return pWA_1;
    case WA_2: return pWA_2;
    case WB_1: return pWB_1;
    case WB_2: return pWB_2;
    case ENA: return pENA;
    case ENB: return pENB;
    }
    qFatal((QString("Unknow pin on WheelPower : ") + QString::number(pinNum)).toStdString().c_str());
    return nullptr;
}

HE10 *ComponentWheelPower::getHE10(int adresse)
{
    switch(adresse) {
    case 0: return he10;
    }
    qFatal((QString("Unknow HE10 on WheelPower : ") + QString::number(adresse)).toStdString().c_str());
    return nullptr;
}

void ComponentWheelPower::onHE10Data(int data)
{
    // HE10 *he10 = static_cast<HE10*>(sender());
    double ENA = pENA->getVoltage();
    bool IN1 = data & 1;
    bool IN2 = data & 2;
    double ENB = pENB->getVoltage();
    bool IN3 = data & 4;
    bool IN4 = data & 8;

    pWA_2->setVoltage(ENA * IN1);
    pWA_1->setVoltage(ENA * IN2);
    pWB_1->setVoltage(ENB * IN3);
    pWB_2->setVoltage(ENB * IN4);
}
