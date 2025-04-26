#include "Ship.h"

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

bool Ship::getOrientation() const {
    return orientation;
}

void Ship::setOrientation(bool orient) {
    orientation = orient;
}

void Ship::shipDamage() {
    shipHealth--;
}
