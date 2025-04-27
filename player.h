#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>
#include <QPoint>
#include "Field.h"
#include "Ship.h"
#include "shotsstrategy.h"

class Player {
public:
    Player(Field* field);
    virtual ~Player();

    virtual Ship* createShip(int w) = 0;
    void createFleet();
    Field* getField();
    bool performShot(QPoint point);
    const QVector<Ship*>& getShips() const { return ships; }

protected:
    Field* field;
    QVector<Ship*> ships;
    ShotsStrategy* shotStrategy;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(Field* field);
    Ship* createShip(int w) override;
};

class AIPlayer : public Player {
public:
    AIPlayer(Field* field);
    Ship* createShip(int w) override;
};

#endif // PLAYER_H
