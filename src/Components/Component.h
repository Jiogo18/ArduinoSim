#ifndef COMPONENT_H
#define COMPONENT_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include "../Links/Pin.h"
#include "../Links/HE10.h"

typedef qreal radian;

class ARDUINO_SIM_EXPORT Component : public QGraphicsPixmapItem
{
public:
    Component(QPixmap pixmap);
    ~Component();

    virtual Pin *getPin(int pinNum);
    virtual HE10 *getHE10(int adresse);

    radian rotation() const;
    void setRotation(radian angle);

protected:
    void setPinVoltage(Pin *pin, int voltage);

};

#endif // COMPONENT_H
