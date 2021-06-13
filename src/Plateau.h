#ifndef PLATEAU_H
#define PLATEAU_H

#include <QGraphicsView>
#include "Robot.h"

class ARDUINO_SIM_EXPORT Plateau : public QGraphicsView
{
public:
    Plateau();
    ~Plateau();
    void setMainRobot(Robot *robot);
    void addRobot(Robot *robot);
    const QImage &getPiste() { return piste; }


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void keyTimerMove();

private:

    QImage piste;
    QList<int> keyPressed;
    QTimer keyTimer;
    Robot *robot = nullptr;
    QList<Robot*> robots;
};

#endif // PLATEAU_H
