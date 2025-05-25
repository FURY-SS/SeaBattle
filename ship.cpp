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

OnePartShip::OnePartShip() {
    weight = 1;

    shipHealth = weight;
}

TwoPartShip::TwoPartShip() {
    weight = 2;

    shipHealth = weight;
}

ThreePartShip::ThreePartShip() {
    weight = 3;

    shipHealth = weight;
}

FourPartShip::FourPartShip() {
    weight = 4;

    shipHealth = weight;
}
