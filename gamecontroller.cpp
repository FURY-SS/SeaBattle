//#include "gamecontroller.h"
#include "QRandomGenerator"

/*
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

bool GameController::canPlaceShip(Player* player, int x, int y, int size, bool horizontal) {
    Field* field = player->getField();

    // Проверяем границы поля
    if (horizontal) {
        if (x + size > 10) return false;
    } else {
        if (y + size > 10) return false;
    }

    // Проверяем соседние клетки
    for (int i = -1; i <= (horizontal ? size : 1); ++i) {
        for (int j = -1; j <= (horizontal ? 1 : size); ++j) {
            int checkX = x + i;
            int checkY = y + j;

            if (checkX >= 0 && checkX < 10 && checkY >= 0 && checkY < 10) {
                if (Field->getCell(checkX, checkY) == CL_SHIP) {
                    return false;
                }
            }
        }
    }

    return true;
}

void GameController::randomPlaceShips(Player* player) {
    Field* field = player->getField();
    field->clear();

    // Размещаем корабли в случайных позициях
    int sizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    for (int size : sizes) {
        bool placed = false;
        while (!placed) {
            int x = QRandomGenerator::global()->bounded(10);
            int y = QRandomGenerator::global()->bounded(10);
            bool horizontal = QRandomGenerator::global()->bounded(2) == 0;

            if (canPlaceShip(player, x, y, size, horizontal)) {
                for (int i = 0; i < size; i++) {
                    int shipX = horizontal ? x + i : x;
                    int shipY = horizontal ? y : y + i;
                    field->setCell(shipX, shipY, CL_SHIP);
                }
                placed = true;
            }
        }
    }
}
*/
