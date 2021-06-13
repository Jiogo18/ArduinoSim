#include "Robot.h"

Robot::Robot() : QGraphicsItemGroup(), QObject()
{
    setTransformOriginPoint(boundingRect().center());
    connect(&moveTimer, &QTimer::timeout, this, &Robot::moveTimeout);
    moveTimer.start(10);
    random = QRandomGenerator::securelySeeded();
}

void Robot::start()
{
    for(ComponentArduino *arduino : arduinos) {
        arduino->start();
    }
}
void Robot::stop()
{
    for(ComponentArduino *arduino : arduinos) {
        arduino->stop();
    }
}

radian Robot::rotation() const
{
    return qDegreesToRadians(QGraphicsItemGroup::rotation());
}

void Robot::setRotation(radian angle)
{
    QGraphicsItem::setRotation(qRadiansToDegrees(angle));
}

void Robot::addRotation(radian angle)
{
    setRotation(rotation() + angle);
}
void Robot::setX(qreal x)
{
    if(x < 0) QGraphicsItemGroup::setX(0);
    else if(x >= 1500) QGraphicsItemGroup::setX(1500);
    else QGraphicsItemGroup::setX(x);
}
void Robot::setY(qreal y)
{
    if(y < 0) QGraphicsItemGroup::setY(0);
    else if(y >= 1100) QGraphicsItemGroup::setY(1100);
    else QGraphicsItemGroup::setY(y);
}
void Robot::addX(qreal x) { setX(this->x() + x); }
void Robot::addY(qreal y) { setY(this->y() + y); }
void Robot::moveLeft(qreal x) { addX(-x); }
void Robot::moveRight(qreal x) { addX(x); }
void Robot::moveUp(qreal y) { addY(-y); }
void Robot::moveDown(qreal y) { addY(y); }

void Robot::registerAsWheel(const ComponentWheel *wheel)
{
    wheels.append(wheel);
    QPointF centre(0, 0);
    for(const ComponentWheel *wheel : wheels) {
        centre += wheel->pos();
    }
    centre /= wheels.length();
    setTransformOriginPoint(centre);
}

void Robot::registerAsArduino(ComponentArduino *arduino)
{
    arduinos.append(arduino);
}

void Robot::toggleStartButton()
{
    if(arduinos.length() == 0) {
        qDebug() << "There is no Arduino to start";
        return;
    }
    if(started) {
        started = false;
        qDebug() << "Stopping" << arduinos.length() << "Arduino...";
        for(ComponentArduino *arduino : arduinos) {
            arduino->stop();
        }
        bool timeout = false;
        for(ComponentArduino *arduino : arduinos) {
            if(arduino->isRunning() && (timeout || !arduino->wait(5000))) {
                qDebug() << "Couldn't stop the Arduino => terminate";
                arduino->terminate();
                timeout = true; // si on a passé 5s sur une carte on terminate toutes les autres
            }
        }
        qDebug() << "Robot stopped!";
    }
    else {
        started = true;
        qDebug() << "Starting" << arduinos.length() << "Arduino...";
        for(ComponentArduino *arduino : arduinos) {
            if(!arduino->isRunning()) arduino->start();
        }
        qDebug() << arduinos.length() << "Robot started!";
    }

}

void Robot::moveTimeout()
{
    if(wheels.length() == 0 || !started) return;

    // point au milieu des roues calculé par registerAsWheel
    QPointF centre = transformOriginPoint();

    QPointF totalResultante(0, 0), BA, R;
    qreal totalMoment = 0, speed, MRB;
    for(const ComponentWheel *wheel : wheels) {
        speed = wheel->getSpeed(random) * 4;
        R = QPointF(-sin(wheel->rotation()) * speed,
                    cos(wheel->rotation()) * speed);

        // BABAR, relation de Varignon
        // M(R_B) = M(R_A) + BA ^ R
        // M(R_A) : moment de la résultante en A (sur la roue) = 0
        // M(R_B) : moment de la résultante en B (le centre) = BA ^ R
        BA = wheel->pos() - centre;

        MRB = BA.x() * R.y() - BA.y() * R.x(); // BA^R
        totalMoment += MRB;
        totalResultante += R;

    }
    totalResultante /= wheels.length();

    // la résultante dépend de la rotation du robot
    addX((totalResultante.x() * cos(rotation()) + totalResultante.y() * sin(rotation())));
    addY((totalResultante.y() * cos(rotation()) + totalResultante.x() * sin(rotation())));
    addRotation(-totalMoment / 2000.0);
}
