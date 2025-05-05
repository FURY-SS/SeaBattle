#include "ship.h"

Ship::Ship() {
    weight = 0;
    shipHealth = 0;
    coords = QPoint(0, 0);
    direction = true;
}

Ship::Ship(int weight) {
    this->weight = weight;
    shipHealth = weight;
    coords = QPoint(0, 0);
    direction = true;
}

QPoint Ship::getCoords() {
    return coords;
}

void Ship::setCoords(QPoint point) {
    coords = point;
}

void Ship::setDirection(bool direction) {
    this->direction = direction;
}

bool Ship::getDirection() {
    return direction;
}

int Ship::getWeight() {
    return weight;
}

int Ship::getHealth() {
    return shipHealth;
}

void Ship::shipDamage() {
    shipHealth--;
}
