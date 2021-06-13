# ArduinoSim

 Simulateur de Robot avec un Arduino

## Comment faire ?

Créer un fichier qui reprend cette fonction main, en modifiant le nombre et la position des composants
Créer un composant spécial qui dérive de ComponentArduino pour programmer `setup` et `loop` (voir l'exemple)
Démarrer votre robot en appuyant sur 'Alt'
Vous pouvez le déplacer avec les flèches directionnelles et le tourner avec Q et D. (Maintenir 'Ctrl' pour déplacer plus vite)

## Who to ?

Create a file with this function, by modifying the number and the position of your components
Create a custom component derivate from ComponentArduino to program `setup` and `loop` (see the example)
Start your robot by pressing 'Alt'
You can move it with the arrow and turn it with Q and D. (Hold 'Ctrl' to move faster)

## Composants

### ComponentArduino

Carte Arduino
Vous devez créer une classe qui hérite de ComponentArduino pour programmer la carte

### ComponentCNY70

Capteur suiveur de ligne
Pin S (0) : niveau de gris de la piste de 0 à 1023

### ComponentWheel

Un moteur et sa roue
Pin W1 (0) et W2 (1) : alimentation du moteur (à relier à la carte de puissance)
Les roues ont des déplacements aléatoires pour rendre la simulation plus réaliste

### ComponentWheelPower

La carte de puissance moteurs
Alimente les moteurs avec un pont en H 
Pins ENA et ENB : alimentation du moteur A et du moteur B
HE10 : relié en I2C pour contrôler le pont en H

### Robot

Ajouter un composant avec `addToGroup()`
Ajouter le robot au plateau avec `addRobot()`
Le premier robot ajouté pourra être déplacé avec le clavier (robot principal)
`setMainRobot()` permet de changer le robot principal
Tous les robots démarrent en appuyant sur Alt, et s'arrêtent après un second appuie.

### Pins

Un pin peut être mis en `INPUT` ou en `OUTPUT`

- `OUTPUT` permet d'écrire une valeur
- `INPUT` permet de lire la valeur du pin connecté

Pour connecter deux pins, il faut utiliser `linkToPin()`.
Le sens n'a pas d'importance, mais pour les exemples j'utilise `pinEnOUTPUT->linkToPin(pinEnINPUT)` avec pinEnOUTPUT et pinEnINPUT qui sont les Pins de deux composants
`digitalRead`, `digitalWrite`, `analogRead` et `analogWrite` sont disponibles pour lire et modifier la tension du pin.
Les autres fonctions seront peut-être acceptées, mais vous ne pourrez pas lancer le programme.

### HE10

Comme les Pins, les connecteurs HE10 se relient avec `linkToHE10()` (peu importe le sens).
Avec la librairie Wire.h, vous pouvez transmettre en HE10.
Attention, la ligne `#include <Wire.h>` n'est pas nécessaire ici, mais il faut le préciser pour un vrai Arduino.
Les connecteurs permettent un transfert de données comme pour du I2C (mais le temps de transfert est négligé).
Pour le moment la carte Arduino peut uniquement envoyer des données.
