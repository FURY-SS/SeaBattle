#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>
#include <QPoint>
#include "Field.h"
#include "shotsstrategy.h"
#include "ship.h"

class Player {
protected:
    Field* field;
    ShotsStrategy* strategy;

public:
    Player();
    virtual ~Player();

    virtual Ship* createShip(int w) = 0;
    void createFleet();
    Field *getField();
    QPoint performShot(QPoint point = QPoint(-1, -1));


};

class HumanPlayer : public Player {
public:
    HumanPlayer() {
        strategy = new ManualShotStrategy();
    }

    Ship* createShip(int w) override;
};

class AIPlayer : public Player {
public:
    AIPlayer() {
        strategy = new RandomShotStrategy();
    }
    Ship* createShip(int w) override;
};

#endif // PLAYER_H
