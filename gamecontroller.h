#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "player.h"
#include <QLabel>

enum GameState {
    SHIPS_PLACING,
    PLAYER_TURN,
    ENEMY_TURN,
    GAMEOVER
};

class GameController {
public:
    GameController(Player* human, Player* ai);
    ~GameController();

    GameState getGameState() const;
    void setGameState(GameState newState);
    void createFleets();
    void swapGameState();

private:
    GameState gameState;
    Player* player;
    Player* bot;
    QLabel* infoLabel;
};

#endif // GAMECONTROLLER_H
