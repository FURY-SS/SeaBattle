#include "gamecontroller.h"

GameController::GameController(Player* human, Player* ai)
    : player(human), bot(ai), gameState(SHIPS_PLACING), infoLabel(nullptr) {}

GameController::~GameController() {
    // Игроки удаляются в MainWindow
}

GameState GameController::getGameState() const {
    return gameState;
}

void GameController::setGameState(GameState newState) {
    gameState = newState;
}

void GameController::createFleets() {
    player->createFleet();
    bot->createFleet();
}

void GameController::swapGameState() {
    if (gameState == ENEMY_TURN)
        setGameState(PLAYER_TURN);
    else if (gameState == PLAYER_TURN)
        setGameState(ENEMY_TURN);
}
