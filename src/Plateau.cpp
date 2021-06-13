#include "Plateau.h"
#include <QKeyEvent>

Plateau::Plateau() : QGraphicsView(new QGraphicsScene)
{
    piste = QImage(":/ressources/plateau");
    scene()->addPixmap(QPixmap::fromImage(piste));

    scale(0.5, 0.5);

    keyTimer.setInterval(10);
    connect(&keyTimer, &QTimer::timeout, this, &Plateau::keyTimerMove);
    grabKeyboard();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

Plateau::~Plateau()
{
    delete scene();
    setScene(nullptr);
}

void Plateau::setMainRobot(Robot *robot)
{
    // Un seul robot est déplacable avec le clavier
    this->robot = robot;
}

void Plateau::addRobot(Robot *robot)
{
    if(!robot) return;

    // Si on n'en a pas encore ajouté il devient le robot principal
    if(robots.isEmpty()) setMainRobot(robot);

    if(!scene()->items().contains(robot)) {
        scene()->addItem(robot);
    }
    robots.append(robot);
}

void Plateau::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;

    switch (event->key()) {
    case Qt::Key_Alt:
        for(Robot *robot : robots) {
            // Démarrer tous les robots
            robot->toggleStartButton();
        }
    }

    if(!keyPressed.contains(event->key())) {
        keyPressed.append(event->key());
    }
    if(!keyTimer.isActive())
        keyTimer.start();
}

void Plateau::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;
    keyPressed.removeAll(event->key());
    if(keyPressed.isEmpty() && keyTimer.isActive())
        keyTimer.stop();
}

void Plateau::keyTimerMove()
{
    if(!robot) return;
    qreal speed = 1;
    if(keyPressed.contains(Qt::Key_Control)) speed = 5;
    if(keyPressed.contains(Qt::Key_Left)) robot->moveLeft(speed);
    if(keyPressed.contains(Qt::Key_Right)) robot->moveRight(speed);
    if(keyPressed.contains(Qt::Key_Up)) robot->moveUp(speed);
    if(keyPressed.contains(Qt::Key_Down)) robot->moveDown(speed);

    if(keyPressed.contains(Qt::Key_Q)) robot->addRotation(-speed / 100.0);
    if(keyPressed.contains(Qt::Key_D)) robot->addRotation(speed / 100.0);
}
