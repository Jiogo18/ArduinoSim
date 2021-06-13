#include <Components/ComponentArduino.h>

// Exemple de programmation à 1 capteur

class ArduinoProgramme : public ComponentArduino {

    #include <Wire.h> // Librairie pour la communication I2C

    // les 3 derniers pins du HE10
    const int capteurM = A0;
    int phase;
    int dL, dR;
    bool dir_last_line;

    bool getCapteurM() { return analogRead(capteurM) < 100; }

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

    void updateLed()
    {
        envoyerLed(0, getCapteurM(), 0, 0, phase >= 0, phase >= 1, phase >= 2, phase >= 3);
    }

    const int droiteArriere = 1;
    const int droiteAvant = 2;
    const int gaucheArriere = 4;
    const int gaucheAvant = 8;
    void arreter() { envoyerMoteur(0); }
    void avancerDroite() { envoyerMoteur(gaucheAvant); }
    void avancerGauche() { envoyerMoteur(droiteAvant); }
    void tournerDroite() { envoyerMoteur(gaucheAvant | droiteArriere); }
    void tournerGauche() { envoyerMoteur(gaucheArriere | droiteAvant); }
    void avancer() { envoyerMoteur(gaucheAvant | droiteAvant); }
    void reculer() { envoyerMoteur(gaucheArriere | droiteArriere); }

    void setup()
    {
        Wire.begin(0x20); // esclave I2C 'Moteurs 12'
        Wire.begin(0x22); // esclave I2C 'S2'
        Serial.begin(9600);

        pinMode(capteurM, INPUT);

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

    int dLeftBlanc(int timeout)
    {
        // trouver du blanc ? => continuer tant qu'on a la ligne
        tournerGauche();
        int start = millis();
        while (getCapteurM() && start + timeout > (int)millis())
        {
            delay(10);
            updateLed();
        }
        arreter();
        start = millis() - start; // durée

        tournerDroite();
        delay(start); // demi tour
        arreter();

        return start >= timeout ? -1 : start; // si timeout
    }

    int dRightBlanc(int timeout)
    {
        // trouver du blanc ? => continuer tant qu'on a la ligne
        tournerDroite();
        int start = millis();
        while (getCapteurM() && start + timeout > (int)millis())
        {
            delay(10);
            updateLed();
        }
        arreter();
        start = millis() - start; // durée

        tournerGauche();
        delay(start); // demi tour
        arreter();

        return start >= timeout ? -1 : start; // si timeout
    }

    int dLeftNoir(int timeout, bool stayIfGood = false)
    {
        // trouver une ligne ?
        tournerGauche();
        int start = millis();
        while (!getCapteurM() && start + timeout > (int)millis())
        {
            delay(10);
            updateLed();
        }
        arreter();
        start = millis() - start; // durée

        if (!stayIfGood || start >= timeout)
        {
            tournerDroite();
            delay(start); // demi tour
            arreter();
        }

        return start >= timeout ? -1 : start; // si timeout
    }

    int dRightNoir(int timeout, bool stayIfGood = false)
    {
        // trouver une ligne ?
        tournerDroite();
        int start = millis();
        while (!getCapteurM() && start + timeout > (int)millis())
        {
            delay(10);
            updateLed();
        }
        arreter();
        start = millis() - start; // durée

        if (!stayIfGood || start >= timeout)
        {
            tournerGauche();
            delay(start); // demi tour
            arreter();
        }

        return start >= timeout ? -1 : start; // si timeout
    }

    void loop()
    {
        phase = -1;
        // retrouver la ligne :
        avancer();
        Serial.println("########## Recherche de la ligne ##########");

        dLeftNoir(200, true);
        if (!getCapteurM())
            dRightNoir(200, true);
        while (!getCapteurM())
        {
            avancer();
            delay(200);
            dLeftNoir(200, true);
            if (!getCapteurM())
                dRightNoir(200, true);
        }
        // on a trouvé la ligne
        phase = 0;
        Serial.println("########## Ligne trouvée ##########");

        do
        {
            avancer();
            delay(50);
            updateLed();

            if (!getCapteurM())
            {
                // il faut recentrer

                if (dir_last_line == 1)
                {
                    // on avait tourné à gauche => prioritée
                    dL = dLeftNoir(300, true);
                    dR = dL == -1 ? dRightNoir(300) : -1; // si dL != -1 alors on peut skip dR
                }
                else
                {
                    // on avait tourné à droite => prioritée
                    dR = dRightNoir(300, true);
                    dL = dR == -1 ? dLeftNoir(300) : -1; // si dR != -1 alors on peut skip dL
                }

                if (dL == -1 && dR == -1)
                {
                    // on l'a perdu => fin ?
                    // il faut aller plus lentement
                    Serial.println("########## Ligne perdue => fin ##########");
                    arreter();
                    delay(1000000);
                    return;
                }
                else if (dL != -1)
                {
                    dir_last_line = 1;
                }
                else
                {
                    dir_last_line = 0;
                }
            }

            dL = dLeftBlanc(120);
            if (dL != -1)
            {
                tournerGauche(); // décaler pour arriver sur
                delay(dL * 1.2); // le blanc et être plus efficace
            }
            Serial.print(dL);
            Serial.print(" ");
            Serial.print(dR);
            Serial.println("");
        } while (dL != -1); // tant que le blanc n'est jamais loins
        // on a du noir à l'infini à gauche ou à droite
        phase = 1;
        Serial.println("########## Début du croisement ##########");

        avancerGauche();
        delay(700);
        while (getCapteurM())
            updateLed(); // attend de sortir
        while (!getCapteurM())
            updateLed(); // attend de retrouver

        dLeftNoir(1000, true); // (sécuritée) essayer de retrouver si ça a pas marché

        phase = 2;
        Serial.println("########## Fin du croisement ##########");
        dir_last_line = 1;

        do
        {
            avancer();
            delay(50);
            updateLed();

            if (!getCapteurM())
            {
                // il faut recentrer

                if (dir_last_line == 1)
                {
                    // on avait tourné à gauche => prioritée
                    dL = dLeftNoir(100, true);
                    dR = dL == -1 ? dRightNoir(100) : -1; // si dL != -1 alors on peut skip dR
                }
                else
                {
                    // on avait tourné à droite => prioritée
                    dR = dRightNoir(100, true);
                    dL = dR == -1 ? dLeftNoir(100) : -1; // si dR != -1 alors on peut skip dL
                }

                if (dL == -1 && dR == -1)
                {
                }
                else if (dL != -1)
                {
                    dir_last_line = 1;
                }
                else if (dR != -1)
                {
                    dir_last_line = 0;
                }
            }
            Serial.print(dL);
            Serial.print(" ");
            Serial.print(dR);
            Serial.println("");
        } while (dL != -1 || dR != -1);
        // on a du noir à l'infini à gauche ou à droite

        phase = 3;
        Serial.println("########## Fin du Parcours ##########");

        arreter(); // FIN
        while (true)
        {
            updateLed();
            delay(100);
        }
    }





};
