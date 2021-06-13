QT += widgets gui

SOURCES += \
    Arduino.cpp \
    Components/Component.cpp \
    Components/ComponentArduino.cpp \
    Components/ComponentCNY70.cpp \
    Components/ComponentWheel.cpp \
    Components/ComponentWheelPower.cpp \
    Example/1Cap/ExMakeRobot1.cpp \
    Example/1Cap/ExProgramme1.cpp \
    Example/2Cap/ExMakeRobot2.cpp \
    Example/2Cap/ExProgramme2.cpp \
    Example/3Cap/ExMakeRobot3.cpp \
    Example/3Cap/ExProgramme3.cpp \
    Links/HE10.cpp \
    Links/Pin.cpp \
    Serial.cpp \
    Wire.cpp \
    Plateau.cpp \
    Robot.cpp

HEADERS += \
    Arduino.h \
    ArduinoSim.h \
    ArduinoSimLibGlobal.h \
    Components/Component.h \
    Components/ComponentArduino.h \
    Components/ComponentCNY70.h \
    Components/ComponentWheel.h \
    Components/ComponentWheelPower.h \
    Links/HE10.h \
    Links/Pin.h \
    Serial.h \
    Wire.h \
    Plateau.h \
    Robot.h

RESOURCES += \
    Component.qrc

DISTFILES += \
    README.md

TEMPLATE = lib
DEFINES += ARDUINO_SIM_LIBRARY
#DEFINES += ARDUINO_SIM_EXAMPLE_1

INCLUDEPATH += ../extern
