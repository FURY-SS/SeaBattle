#include "ship.h"

Ship::Ship() {}

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

void Ship::setDirection(bool dir) {
    direction = dir;
}

bool Ship::getDirection() {
    return direction;
}
