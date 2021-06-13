#include "Component.h"

Component::Component(QPixmap pixmap) : QGraphicsPixmapItem(pixmap)
{
    setTransformOriginPoint(boundingRect().center());
}

Component::~Component() {}

Pin *Component::getPin(int pinNum)
{
    Q_UNUSED(pinNum);
    return nullptr;
}

HE10 *Component::getHE10(int adresse)
{
    Q_UNUSED(adresse);
    return nullptr;
}

radian Component::rotation() const
{
    return qDegreesToRadians(QGraphicsPixmapItem::rotation());
}

void Component::setRotation(radian angle)
{
    return QGraphicsPixmapItem::setRotation(qRadiansToDegrees(angle));
}

void Component::setPinVoltage(Pin *pin, int voltage)
{
    Q_ASSERT(pin);
    pin->setPinMode(OUTPUT);
    pin->setVoltage(voltage);
}
