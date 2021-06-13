#include <QtWidgets/QApplication>
#include <ArduinoSim.h>

// Les composants utilis�s :
#include "ArduinoACoder.cpp" // Une carte Arduino programm�e
#include <Components/ComponentCNY70.h>
#include <Components/ComponentWheel.h>
#include <Components/ComponentWheelPower.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Plateau plateau;
    const QImage* piste = &plateau.getPiste();


    SerialLib::println("Cr�ation du robot...");
    Robot* robot = new Robot;

    ////////// Ajouter des composants //////////
    // Ajoutez des composants ici



    ////////// Connecter les pins //////////
    // Connectez les pins ici



    ///// Vous pouvez ajouter auttant de robot que vous voulez avec addRobot
    plateau.addRobot(robot);

    // Positionner le robot
    robot->setRotation(HALF_PI);
    robot->setPos(280, 200);

    SerialLib::println("Robot Cr�� ! Appuyez sur 'Alt' pour d�marrer votre/vos robot(s)");
    plateau.show();
    return app.exec();
}
