#ifndef ARDUINO_H
#define ARDUINO_H

// Ce fichier sert uniquement pour les constantes
#include "Arduino-master/cores/esp8266/Arduino.h"
#include "ArduinoSimLibGlobal.h"

// Attention, les fonctions millis, micros and micros64 ne retournent pas un timestamp (temps depuis 1970)
// Elles retournent le temps local depuis que l'Arduino (le prgramme) est démarré
ARDUINO_SIM_EXPORT unsigned long int millis();
ARDUINO_SIM_EXPORT unsigned long int micros();
ARDUINO_SIM_EXPORT unsigned long int micros64();
ARDUINO_SIM_EXPORT void delay(long ms);
ARDUINO_SIM_EXPORT void delayMicroseconds(int us);


#endif // ARDUINO_H
