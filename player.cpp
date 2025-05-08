#include "Player.h"
#include "ship.h"

Player::Player() {
    field = new Field();
}

Player::~Player() {}

void Player::createFleet() {

    field->addShip(createShip(4));

    for (int i {0}; i < 2; i++) {
        field->addShip(createShip(3));
    }

    for (int i {0}; i < 3; i++) {
        field->addShip(createShip(2));
    }

    for (int i {0}; i < 4; i++) {
        field->addShip(createShip(1));
    }
}

Field* Player::getField() {
    return field;
}

QPoint Player::performShot(QPoint point) {
    return strategy->shot(point);
}

Ship* HumanPlayer::createShip(int w) {
    switch (w) {
    case 1:
        return new OnePartShip();
    case 2:
        return new TwoPartShip();
    case 3:
        return new ThreePartShip();
    case 4:
        return new FourPartShip();
    default:
        qDebug() << "Введен некорректный вес корабля";
        return nullptr;
    }
}

Ship* AIPlayer::createShip(int w) {
    switch (w) {
    case 1:
        return new OnePartShip();
    case 2:
        return new TwoPartShip();
    case 3:
        return new ThreePartShip();
    case 4:
        return new FourPartShip();
    default:
        qDebug() << "Введен некорректный вес корабля";
        return nullptr;
    }
}

