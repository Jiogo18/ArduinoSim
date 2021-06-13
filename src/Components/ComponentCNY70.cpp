#include "ComponentCNY70.h"

ComponentCNY70::ComponentCNY70(const QImage *piste) : Component(QPixmap(":/ressources/sensorOff")), piste(piste)
{
    pGND = new Pin(GND);
    p0 = new Pin(S);
    pEN = new Pin(EN);

    setPinVoltage(pGND, 0);
    setPinVoltage(p0, 0);
    setPinVoltage(pEN, 1023);
}

ComponentCNY70::~ComponentCNY70()
{
    delete pGND;
    delete p0;
    delete pEN;
}

Pin *ComponentCNY70::getPin(int pinNum)
{
    switch (pinNum) {
    case GND: return pGND;
    case S: return p0;
    case EN: return pEN;
    }
    qFatal((QString("Unknow pin on CNY70 : ") + QString::number(pinNum)).toStdString().c_str());
    return nullptr;
}

qreal ComponentCNY70::getValue() const
{
    if(!piste) return 0;
    QPoint pos = getSensorPos().toPoint();
    if(!piste->rect().contains(pos)) return 0;
    QRgb couleur = piste->pixel(pos);
    // value entre 0 et 768 (3*256)
    int value = ( (couleur % 256) + ((couleur / 256) % 256) + ((couleur / 256 / 256) % 256) );
    // https://www.mouser.fr/datasheet/2/427/cny70-1767236.pdf
    // sur du blanc (value = 768) le courant est fort et la tension est faible
    // sur du noir (value = 0) le courant est faible et la tension est forte
    // MAIS le code que j'avais fait m'indique l'inverse :
    //    la ligne => du noir => 0 (<100) => LOW
    return value * 5.0 / 768; // max : 5 V environ
}

void ComponentCNY70::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    p0->setVoltage(getValue());
    if(p0->getVoltage() <= 2) {
        painter->drawPixmap(0, 0, QPixmap(":/ressources/sensorOn"));
    }
    else {
        painter->drawPixmap(0, 0, QPixmap(":/ressources/sensorOff"));
    }

    // pas besoin de thread si on actualise avec paint
    // seulement c'est peut-être pas actu si la fenetre est masquée
}

QPointF ComponentCNY70::getSensorPos() const
{
    qreal rot = rotation() + (parentItem() ? qDegreesToRadians(parentItem()->rotation()) : 0);
    QPointF center = sceneBoundingRect().center();

    QPointF decalage(7, 0);

    return center + QPointF(cos(rot) * decalage.x() + sin(rot) * decalage.y(),
                            sin(rot) * decalage.x() + cos(rot) * decalage.y());
}
