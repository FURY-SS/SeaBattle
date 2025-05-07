#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Field.h"
#include "ship.h"
#include "player.h"
#include <QLabel>

enum GameState {
    SHIPS_PLACING,
    PLAYER_TURN,
    ENEMY_TURN,
    GAMEOVER
};

class GameController {
    GameState gameState;
    Player* player;
    Player* bot;

public:
    GameController();
    ~GameController();

    GameState getGameState();

    void createFlots();

    int getPlayerShipCellsCount();
    int getBotShipCellsCount();

    bool isPlayerEmptyCell(QPoint point);
    bool isBotEmptyCell(QPoint point);

    void setPlayerCellState(QPoint point, int stateNum);
    void setBotCellState(QPoint point, int stateNum);

    Cell getBotCellState(QPoint point);
    Cell getPlayerCellState(QPoint point);

    void printPlayerAllCellStates();
    void printBotAllCellStates();

    QVector<Cell> getPlayerAllCells();
    QVector<Cell> getBotAllCells();

    QLabel *infoLabel;
};

#endif // GAMECONTROLLER_H
