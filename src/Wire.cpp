#include "Wire.h"

WireLib::WireLib() {}

WireLib::WireLib(QList<HE10*> he10s) : he10s(he10s) {}

void WireLib::beginTransmission(int adresse)
{
    he10Transmission = getHE10(adresse);
    dataTransmission = 0;
}

void WireLib::begin(int adresse)
{
    he10Transmission = getHE10(adresse);
}

void WireLib::write(int data)
{
    dataTransmission = data;
}

void WireLib::endTransmission()
{
    if(he10Transmission) {
        he10Transmission->sendData(dataTransmission);
    }
    dataTransmission = 0;
}

HE10 *WireLib::getHE10(int adresse)
{
    for(HE10 *he10 : he10s) {
        if(he10->getAdresse() == adresse) {
            return he10;
        }
    }
    return nullptr;
}
