#include "ComponentWheel.h"

ComponentWheel::ComponentWheel() : Component(QPixmap(":/ressources/moteur.png").scaledToWidth(100))
{
    pW1 = new Pin(W1);
    pW2 = new Pin(W2);
    pW1->setPinMode(INPUT);
    pW2->setPinMode(INPUT);
    setTransformOriginPoint(boundingRect().center() + QPoint(45, 0)); // position de la roue
}

Pin *ComponentWheel::getPin(int pinNum)
{
    switch (pinNum) {
    case W1: return pW1;
    case W2: return pW2;
    }
    qFatal((QString("Unknow pin on Wheel : ") + QString::number(pinNum)).toStdString().c_str());
    return nullptr;
}

QPointF ComponentWheel::wheelContactPoint() const
{
    return transformOriginPoint();
}

double ComponentWheel::getSpeed(QRandomGenerator &randomSpeed) const
{
    double speed = (pW2->getVoltage() - pW1->getVoltage()) / 10; // 0 - 1
    double noise = (randomSpeed.generateDouble() + 0.5); // 50 % - 150 %
    return speed * noise; // delta potentiel = tension ~= vitesse des roues
}
