#include "Components/ComponentArduino.h"

// Exemple de programmation à 3 capteurs

class ArduinoProgrammeExemple3 : public ComponentArduino {

    // TEST final 7 (avec leds)
    // FONCTIONNE !!!

    #include <Wire.h> // Librairie pour la communication I2C

    // les 3 derniers pins du HE10
    const int capteurG = A1, capteurM = A0, capteurD = A2;
    int phase;
    bool etatG, etatM, etatD;

    bool getCapteurG() { return analogRead(capteurG) < 100; }
    bool getCapteurM() { return analogRead(capteurM) < 100; }
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
        pinMode(capteurM, INPUT);
        pinMode(capteurD, INPUT);

        // Activation 1, 2, 3 et 4 du L293D
        pinMode(5, OUTPUT);
        pinMode(6, OUTPUT);
        digitalWrite(5, HIGH);
        digitalWrite(6, HIGH);
        //analogWrite(5, 255);
        //analogWrite(6, 255);

        phase = 0;
        avancer();
    }

    void updateLed()
    {
        envoyerLed(etatG, etatM, etatD, 0, phase >= 0, phase >= 1, phase >= 2, phase >= 3);
    }

    void suitLaLigne()
    {
        etatG = getCapteurG();
        etatM = getCapteurM();
        etatD = getCapteurD();

        if (etatG && etatD)
        {
            avancer(); // 3 capteurs sur la ligne ou dans un coins de ligne
        }
        else if (etatG)
        {
            avancerGauche(); // capteur gauche sur la ligne
            do
            {
                delay(10);
            } while (!getCapteurM());
        }
        else if (etatD)
        {
            avancerDroite(); // capteur droit sur la ligne
            do
            {
                delay(10);
            } while (!getCapteurM());
        }
        else if (etatM)
        {
            avancer(); // juste le capteur du milieu
        }
        else
        {
            avancer(); // aucun capteur = ligne perdue (mais on avance quand même)
        }
    }

    void loop()
    {
        etatG = getCapteurG();
        etatM = getCapteurM();
        etatD = getCapteurD();

        Serial.print(analogRead(capteurG));
        Serial.print(" ");
        Serial.print(analogRead(capteurM));
        Serial.print(" ");
        Serial.print(analogRead(capteurD));
        Serial.println(" ");

        switch (phase)
        {
        case 0:
            if (etatG && etatM && etatD)
            { // 3 capteurs sur la ligne
                avancerGauche();
                Serial.println("=> phase 1");
                phase = 1;
                delay(500);
                updateLed();

                do
                {
                } while (getCapteurG() != false || getCapteurM() != true || getCapteurD() != false);
                // on a tourné suffisamment pour retrouver la ligne
                Serial.println("=> phase 2");
                phase = 2;
            }
            else
            {
                suitLaLigne();
            }
            break;
        case 1:
            envoyerLed(0, 0, 0, 0, 0, 1, 0, 0);
            break;
        case 2:
            if (etatG && etatM && etatD)
            { // 3 capteurs sur la ligne
                phase = 3;
                Serial.println("=> phase 3 (end)");
                arreter();
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
        } while (etatG == getCapteurG() && etatM == getCapteurM() && etatD == getCapteurD());
    }





};
