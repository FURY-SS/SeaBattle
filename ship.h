#ifndef SHIP_H
#define SHIP_H

#include <QDebug>
#include <QPoint>

class Ship {
    int weight;       // размер корабля (1-4)
    QPoint coords;    // нос корабля
    bool direction;   // true = горизонтально, false = вертикально
    int shipHealth;   // оставшееся здоровье

public:
    Ship();
    Ship(int weight);

    QPoint getCoords();
    void setCoords(QPoint point);

    void setDirection(bool direction);
    bool getDirection();

    int getWeight();
    int getHealth();

    void shipDamage();
};

#endif // SHIP_H
