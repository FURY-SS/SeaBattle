#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "player.h"
#include <QLabel>
#include <unistd.h>
#include "shotsstrategy.h"

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

    bool checkPlayerShipPlacement();
    bool checkBotShipPlacement();

    void takeShot(Player* whoShots, Player* whoseField, QPoint point);
    void playerShot(QPoint point);

    void swapGameState();
    int checkForGameOver();
    void setGameState(GameState newState);
    void botShot();
    void botRandomShipsPlacing();
    void syncPlayerShipsCells();
    void syncBotShipsCells();
};

#endif // GAMECONTROLLER_H
