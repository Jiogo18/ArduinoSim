#ifdef ARDUINO_SIM_EXAMPLE_1

#include <QApplication>
#include "ArduinoSim.h"

// Les composants utilisés :
#include "ExProgramme1.cpp" // Une carte Arduino programmée
#include "Components/ComponentCNY70.h"
#include "Components/ComponentWheel.h"
#include "Components/ComponentWheelPower.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Plateau plateau;
    const QImage *piste = &plateau.getPiste();


    SerialLib::println("Création du robot...");
    Robot *robot = new Robot;

    ////////// Ajouter des composants //////////
    // 1 carte Arduino
    ArduinoProgrammeExemple1 *arduino = new ArduinoProgrammeExemple1();
    robot->addToGroup(arduino);
    robot->registerAsArduino(arduino);

    // 1 capteurs
    ComponentCNY70 *sensorM = new ComponentCNY70(piste);
    robot->addToGroup(sensorM);
    sensorM->setPos(190, 60);

    // 2 roues
    ComponentWheelPower *wheelPower = new ComponentWheelPower();
    robot->addToGroup(wheelPower);
    ComponentWheel *roueGauche = new ComponentWheel();
    roueGauche->setRotation(-HALF_PI);
    roueGauche->setPos(-25, -25);
    robot->addToGroup(roueGauche);
    robot->registerAsWheel(roueGauche);
    ComponentWheel *roueDroite = new ComponentWheel();
    roueDroite->setRotation(HALF_PI);
    roueDroite->setPos(-25, 140);
    robot->addToGroup(roueDroite);
    robot->registerAsWheel(roueDroite);


    ////////// Connecter les pins //////////
    // Arduino => Carte de puissance moteur
    arduino->getPin(ComponentArduino::D5)->linkToPin(wheelPower->getPin(ComponentWheelPower::ENA));
    arduino->getPin(ComponentArduino::D6)->linkToPin(wheelPower->getPin(ComponentWheelPower::ENB));
    arduino->getHE10(0x20)->linkToHE10(wheelPower->getHE10(0)); // (HE10_MOTEURS_12 == 0x20)

    // Carte de puissance moteur => Roue
    wheelPower->getPin(ComponentWheelPower::WA_1)->linkToPin(roueDroite->getPin(ComponentWheel::W1));
    wheelPower->getPin(ComponentWheelPower::WA_2)->linkToPin(roueDroite->getPin(ComponentWheel::W2));
    wheelPower->getPin(ComponentWheelPower::WB_1)->linkToPin(roueGauche->getPin(ComponentWheel::W1));
    wheelPower->getPin(ComponentWheelPower::WB_2)->linkToPin(roueGauche->getPin(ComponentWheel::W2));

    // Capteur CNY70 => Arduino
    sensorM->getPin(ComponentCNY70::S)->linkToPin(arduino->getPin(ComponentArduino::A0));


    ///// Vous pouvez ajouter auttant de robot que vous voulez avec addRobot
    plateau.addRobot(robot);

    // Positionner le robot
    robot->setRotation(HALF_PI);
    robot->setPos(280, 200);

    SerialLib::println("Robot Créé ! Appuyer sur 'Alt' pour démarrer votre/vos robot(s)");
    plateau.show();
    return app.exec();
}

#endif // ARDUINO_SIM_EXAMPLE_1
