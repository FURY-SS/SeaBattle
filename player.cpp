#include "Player.h"
#include "ShotsStrategy.h"

Player::Player(Field* field) : field(field), shotStrategy(nullptr) {}

Player::~Player() {
    for (Ship* ship : ships) {
        delete ship;
    }
    delete shotStrategy;
}

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
    if (w == 1) return new OnePartShip();
    if (w == 2) return new TwoPartShip();
    if (w == 3) return new ThreePartShip();
    if (w == 4) return new FourPartShip();
    return nullptr;
}

AIPlayer::AIPlayer(Field* field) : Player(field) {
    shotStrategy = new RandomShotStrategy(field);
}

Ship* AIPlayer::createShip(int w) {
    if (w == 1) return new OnePartShip();
    if (w == 2) return new TwoPartShip();
    if (w == 3) return new ThreePartShip();
    if (w == 4) return new FourPartShip();
    return nullptr;
}
