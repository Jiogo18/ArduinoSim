#include "Components/ComponentArduino.h"

// Exemple de programmation à 2 capteurs

class ArduinoProgrammeExemple2 : public ComponentArduino {

    // TEST final avec 2 capteurs !!!
    // FONCTIONNE !!!

    #include <Wire.h> // Librairie pour la communication I2C

    // les 3 derniers pins du HE10
    const int capteurG = A1, capteurD = A2;
    int phase;
    bool etatG, etatD;

    bool getCapteurG() { return analogRead(capteurG) < 100; }
    bool getCapteurD() { return analogRead(capteurD) < 100; }

    void envoyerMoteur(int xO)
    {
        Wire.beginTransmission(0x20); // esclave I2C 'Moteurs 12'
        Wire.write(xO);
        Wire.endTransmission();
    }
    void envoyerLed(bool l1, bool l2, bool l3, bool l4, bool l5, bool l6, bool l7, bool l8)
    {
        Wire.beginTransmission(0x22); // esclave I2C 'S2'
        Wire.write((int)l1 | l2 * 2 | l3 * 4 | l4 * 8 | l5 * 16 | l6 * 32 | l7 * 64 | l8 * 128);
        Wire.endTransmission();
    }

    const int droiteArriere = 1;
    const int droiteAvant = 2;
    const int gaucheArriere = 4;
    const int gaucheAvant = 8;
    void arreter() { envoyerMoteur(0); }
    void avancerDroite() { envoyerMoteur(gaucheAvant); }
    void avancerGauche() { envoyerMoteur(droiteAvant); }
    void avancer() { envoyerMoteur(gaucheAvant | droiteAvant); }
    void reculer() { envoyerMoteur(gaucheArriere | droiteArriere); }

    void setup()
    {
        Wire.begin(0x20); // esclave I2C 'Moteurs 12'
        Wire.begin(0x22); // esclave I2C 'S2'
        Serial.begin(9600);

        pinMode(capteurG, INPUT);
        pinMode(capteurD, INPUT);

        // Activation 1, 2, 3 et 4 du L293D
        pinMode(5, OUTPUT);
        pinMode(6, OUTPUT);
        //digitalWrite(5, HIGH);
        //digitalWrite(6, HIGH);
        analogWrite(5, 220);
        analogWrite(6, 220);

        phase = 0;
        avancer();
    }

    void updateLed()
    {
        envoyerLed(etatG, 0, etatD, 0, phase >= 0, phase >= 1, phase >= 2, phase >= 3);
    }

    // version 2 capteurs :
    void suitLaLigne()
    {
        etatG = getCapteurG();
        etatD = getCapteurD();

        if (etatG && etatD)
        {
            avancer(); // 2 capteurs sur la ligne ou on est dans un coins ou à la fin
        }
        else if (etatG == true)
        {
            avancerGauche();
        }
        else if (etatD == true)
        {
            avancerDroite();
        }
        else
        { // ligne en dessous (on sait pas si elle est perdue...)
            avancer();
        }
    }

    void loop()
    {
        etatG = getCapteurG();
        etatD = getCapteurD();

        Serial.print(analogRead(capteurG));
        Serial.print(" ");
        Serial.print(analogRead(capteurD));
        Serial.println(" ");

        switch (phase)
        {
        case 0:
            if (etatG && etatD)
            { // 2 capteurs sur la ligne
                avancerGauche();
                Serial.println("=> phase 1");
                phase = 1;
                delay(500);
            }
            else
            {
                suitLaLigne();
            }
            break;
        case 1:
            if (etatG == true)
            {
                Serial.println("=> phase 2");
                phase = 2;
            }
            break;
        case 2:
            if (etatG && etatD)
            { // 3 capteurs sur la ligne
                phase = 3;
                Serial.println("=> phase 3 (end)");
                arreter();
                return;
            }
            else
            {
                suitLaLigne();
            }
            break;
        }
        updateLed();

        delay(10); // permet de faire durer les mouvements, pour pas faire gauche/avant instant
        do
        {
            delay(1);
        } while (etatG == getCapteurG() && etatD == getCapteurD());
    }





};
