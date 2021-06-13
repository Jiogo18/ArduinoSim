#include <Components/ComponentArduino.h>

class ArduinoProgramme : public ComponentArduino
{

    // Votre code commence ici (comme si c'était l'IDE d'Arduino)

    void setup()
    {
        Serial.begin(9600);
        Serial.println("setup");
    }

    void loop()
    {
        Serial.println("loop");
        delay(1000);
    }

    // Fin du code

};