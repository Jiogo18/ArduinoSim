#ifndef COMPONENTWHEEL_H
#define COMPONENTWHEEL_H

#include "Component.h"
#include <QtCore/QRandomGenerator>

class ARDUINO_SIM_EXPORT ComponentWheel : public Component
{
public:
    enum pins {
        W1 = 0,
        W2 = 1,
    };
    ComponentWheel();

    Pin *getPin(int pinNum) override;
    QPointF wheelContactPoint() const;

    double getSpeed(QRandomGenerator &randomSpeed) const;

private:
    Pin *pW1;
    Pin *pW2;
};

#endif // COMPONENTWHEEL_H
