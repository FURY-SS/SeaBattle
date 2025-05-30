#ifndef SHIP_H
#define SHIP_H

#include <QPoint>

class Ship {
protected:
    int weight;       // размер корабля (1-4)
    QPoint coords;    // нос корабля
    bool direction;   // true = горизонтально, false = вертикально
    int shipHealth;   // оставшееся здоровье

public:
    Ship();

    int getWeight();
    void setCoords(QPoint point);
    int getHealth();
    QPoint getCoords();
    void shipDamage();

    void setDirection(bool dir);
    bool getDirection();
};

class OnePartShip : public Ship {
public:
    OnePartShip();
};

class TwoPartShip : public Ship {
public:
    TwoPartShip();
};

class ThreePartShip : public Ship {
public:
    ThreePartShip();
};

class FourPartShip : public Ship {
public:
    FourPartShip();
};

#endif
