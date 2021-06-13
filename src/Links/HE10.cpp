#include "HE10.h"

HE10::HE10(int adresse) : adresse(adresse) {}

HE10::~HE10()
{
    linkToHE10(nullptr); // unlink
}

int HE10::getAdresse() const
{
    return adresse;
}

void HE10::linkToHE10(HE10 *he10)
{
    if(he10Linked) {
        // delink
        he10Linked->he10Linked = nullptr;
    }
    he10Linked = he10;
    if(he10Linked) {
        // link
        he10Linked->he10Linked = this;
    }
}

void HE10::sendData(int data)
{
    if(he10Linked) {
        emit he10Linked->onData(data);
    }
}
