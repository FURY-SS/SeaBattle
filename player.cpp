#include "Player.h"

Player::Player(Field* field) : field(field), shotStrategy(nullptr) {}

Player::~Player() {}

void Player::createFleet() {
    ships.append(createShip(4));

    for (int i = 0; i < 2; i++) {
        ships.append(createShip(3));
    }

    for (int i = 0; i < 3; i++) {
        ships.append(createShip(2));
    }

    for (int i = 0; i < 4; i++) {
        ships.append(createShip(1));
    }
}

Field* Player::getField() {
    return field;
}

bool Player::performShot(QPoint point) {
    if (shotStrategy) {
        QPoint shotPoint = shotStrategy->makeShot(point);
        return field->getCell(shotPoint.x(), shotPoint.y()) == CL_CLEAR;
    }
    return false;
}

HumanPlayer::HumanPlayer(Field* field) : Player(field) {
    shotStrategy = new ManualShotStrategy(field);
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
        return nullptr;
    }
}

AIPlayer::AIPlayer(Field* field) : Player(field) {
    shotStrategy = new RandomShotStrategy(field);
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
        return nullptr;
    }
}
