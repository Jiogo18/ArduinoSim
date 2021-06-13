#ifndef ROBOT_H
#define ROBOT_H

#include <QGraphicsItemGroup>
#include <QTimer>
#include <QList>
#include "Components/Component.h"
#include "Components/ComponentWheel.h"
#include "Components/ComponentArduino.h"

class ARDUINO_SIM_EXPORT Robot : public QGraphicsItemGroup, public QObject
{
public:
    Robot();
    virtual void start();
    virtual void stop();

    radian rotation() const;
    void setRotation(radian angle);
    void addRotation(radian angle);

    void setX(qreal x);
    void setY(qreal y);
    void addX(qreal x);
    void addY(qreal y);
    void moveLeft(qreal x);
    void moveRight(qreal x);
    void moveUp(qreal y);
    void moveDown(qreal y);

    void registerAsWheel(const ComponentWheel *wheel);
    void registerAsArduino(ComponentArduino *arduino);

    void toggleStartButton();

private slots:
    void moveTimeout();

private:
    QTimer moveTimer;
    QList<const ComponentWheel *> wheels;
    QList<ComponentArduino*> arduinos;
    bool started = false;

    QRandomGenerator random;


};


#endif // ROBOT_H
