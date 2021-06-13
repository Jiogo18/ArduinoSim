#ifndef COMPONENTCNY70_H
#define COMPONENTCNY70_H

#include "Component.h"

class ARDUINO_SIM_EXPORT ComponentCNY70 : public Component
{
public:
    enum pins {
        S = 0,
        GND = 1,
        EN = 2
    };
    ComponentCNY70(const QImage *piste);
    ~ComponentCNY70();

    Pin *getPin(int pinNum) override;
    qreal getValue() const;


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    Pin *pGND;
    Pin *p0;
    Pin *pEN;
    const QImage *piste = nullptr;
    QPointF getSensorPos() const;
};

#endif // COMPONENTCNY70_H
