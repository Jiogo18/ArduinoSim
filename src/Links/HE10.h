#ifndef HE10_H
#define HE10_H

#include <QtCore/QObject>
#include "ArduinoSimLibGlobal.h"

class ARDUINO_SIM_EXPORT HE10 : public QObject
{
    Q_OBJECT
public:
    HE10(int adresse);
    ~HE10();
    int getAdresse() const;

    void linkToHE10(HE10 *he10);

    void sendData(int data);

signals:
    void onData(int data);

private:
    int adresse;
    HE10 *he10Linked = nullptr;
};

#endif // HE10_H
