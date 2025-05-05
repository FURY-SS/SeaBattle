#include "ship.h"

int Ship::getWeight() {
    return weight;
}

void Ship::setCoords(QPoint point) {
    coords = point;
}

int Ship::getHealth() {
    return shipHealth;
}

QPoint Ship::getCoords() {
    return coords;
}

void Ship::shipDamage() {
    shipHealth--;
}
