#include "gamecontroller.h"

GameController::GameController() {
    gameState = GameState::SHIPS_PLACING;

    player = new HumanPlayer();
    bot = new AIPlayer();

    createFlots();
}

GameController::~GameController() {
    delete player;
    delete bot;
}

GameState GameController::getGameState() {
    return gameState;
}

void GameController::createFlots() {
    player->createFleet();
    bot->createFleet();
}

int getShipCellsCount(Player* somePlayer) {
    int count = 0;

    Field* field = somePlayer->getField();

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (field->getCellState(QPoint(j, i)) == Cell::SHIP)
                count++;
        }
    }

    return count;
}

int GameController::getPlayerShipCellsCount() {
    return getShipCellsCount(player);
}

int GameController::getBotShipCellsCount() {
    return getShipCellsCount(bot);
}

bool isEmptyCell(Player* somePlayer, QPoint point) {
    Field* field = somePlayer->getField();

    return field->getCellState(point) == Cell::EMPTY;
}

bool GameController::isPlayerEmptyCell(QPoint point) {
    return isEmptyCell(player, point);
}

bool GameController::isBotEmptyCell(QPoint point) {
    return isEmptyCell(bot, point);
}

void setCellState(Player* somePlayer, QPoint point, int stateNum) {
    Field* field = somePlayer->getField();

    field->setCellState(point, static_cast<Cell>(stateNum));
}

void GameController::setBotCellState(QPoint point, int stateNum) {
    setCellState(bot, point, stateNum);
}

void GameController::setPlayerCellState(QPoint point, int stateNum) {
    setCellState(player, point, stateNum);
}

Cell getCellState(QPoint point, Player* somePlayer) {
    Field* field = somePlayer->getField();

    return field->getCellState(point);
}

Cell GameController::getBotCellState(QPoint point) {
    return getCellState(point, bot);
}

Cell GameController::getPlayerCellState(QPoint point) {
    return getCellState(point, player);
}

void printAllCellStates(Player* somePlayer) {
    somePlayer->getField()->printFieldStates();
}

void GameController::printPlayerAllCellStates() {
    printAllCellStates(player);
}

void GameController::printBotAllCellStates() {
    printAllCellStates(bot);
}

QVector<Cell> getAllCells(Player* somePlayer) {
    return somePlayer->getField()->getCells();
}

QVector<Cell> GameController::getPlayerAllCells() {
    return getAllCells(player);
}

QVector<Cell> GameController::getBotAllCells() {
    return getAllCells(bot);
}

bool isShip(Player* somePlayer, int size, int x, int y) {
    Field* field = somePlayer->getField();

    if (x > 0 && field->getCellState(QPoint(x - 1, y)) != Cell::EMPTY) {
        return false;
    }

    if (y > 0 && field->getCellState(QPoint(x, y - 1)) != Cell::EMPTY) {
        return false;
    }

    if (field->getCellState(QPoint(x, y)) == Cell::EMPTY) {
        return false;
    }

    int tmp = x;
    int num = 0;

    while (field->getCellState(QPoint(tmp, y)) != Cell::EMPTY && tmp < 10) {
        tmp++;
        num++;
    }

    if (num == size) {
        if (field->getCellState(QPoint(x, y + 1)) != Cell::EMPTY) {
            return false;
        }

        if (field->getCellState(QPoint(x - 1, y - 1)) != Cell::EMPTY || field->getCellState(QPoint(x - 1, y + 1)) != Cell::EMPTY || field->getCellState(QPoint(x + size, y - 1)) != Cell::EMPTY || field->getCellState(QPoint(x + size, y + 1)) != Cell::EMPTY) {
            return false;
        }

        return true;
    }

    tmp = y;
    num = 0;

    while (field->getCellState(QPoint(x, tmp)) != Cell::EMPTY && tmp < 10) {
        tmp++;
        num++;
    }

    if (num == size) {
        if (field->getCellState(QPoint(x + 1, y)) != Cell::EMPTY) {
            return false;
        }

        if (field->getCellState(QPoint(x - 1, y - 1)) != Cell::EMPTY || field->getCellState(QPoint(x + 1, y - 1)) != Cell::EMPTY || field->getCellState(QPoint(x - 1, y + size)) != Cell::EMPTY || field->getCellState(QPoint(x + 1, y + size)) != Cell::EMPTY) {
            return false;
        }

        return true;
    }

    return false;
}

int shipNum(Player* somePlayer, int size) {
    int shipNumber = 0;

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(isShip(somePlayer, size, j, i))
                shipNumber++;

    return shipNumber;
}

bool GameController::checkShipPlacement(Player *somePlayer) {
    // проверка на кол-во кораблей, должно быть 20
    if (getShipCellsCount(somePlayer) == 20) {
        if (shipNum(somePlayer, 1) == 4 &&
            shipNum(somePlayer, 2) == 3 &&
            shipNum(somePlayer, 3) == 2 &&
            shipNum(somePlayer, 4) == 1) {

            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

bool GameController::checkPlayerShipPlacement() {
    return checkShipPlacement(player);
}

bool GameController::checkBotShipPlacement() {
    return checkShipPlacement(bot);
}

void GameController::takeShot(Player* whoShots, Player* whoseField, QPoint point) {
    Field* field = whoseField->getField();
    QPoint shotedPoint = whoShots->performShot(point);


    if (field->getCellState(shotedPoint) == Cell::EMPTY) {
        field->setCellState(shotedPoint, Cell::DOT);
        // TODO: переход к ходу бота
        swapGameState();
        if (getGameState() == GameState::ENEMY_TURN)
            infoLabel->setText("Ход Бота!");
        else {
            infoLabel->setText("Ваш ход!");
        }

    } else if (field->getCellState(shotedPoint) == Cell::SHIP) {
        // обработка попадания по кораблю
        // если корабль подбили - поставить Cell::DAMAGED, если убили - DEAD

        Ship* shotedShip = field->getShipByCell(shotedPoint);
        shotedShip->shipDamage();

        int shipHealth = shotedShip->getHealth();

        field->setCellState(shotedPoint, Cell::DAMAGED);

        if (shipHealth != 0) {
            // не добили
            int d = 0;
        } else {
            // убили
            // установка всех клеток, пренадлежащих кораблю в статус DEAD
            if (field->getCellState(QPoint(shotedShip->getCoords().x() + 1, shotedShip->getCoords().y())) == Cell::DAMAGED || shotedShip->getWeight() == 1) {
                // ориентация горизонтальная
                for (int i {0}; i < shotedShip->getWeight(); i++) {
                    field->setCellState(QPoint(shotedShip->getCoords().x() + i, shotedShip->getCoords().y()), Cell::DEAD);
                }

                // расстановка точек вокруг мертвого корабля по горизонтали
                for (int i {-1}; i < shotedShip->getWeight() + 1; i++) {
                    field->setCellState(QPoint(shotedShip->getCoords().x() + i, shotedShip->getCoords().y() + 1), Cell::DOT);
                    field->setCellState(QPoint(shotedShip->getCoords().x() + i, shotedShip->getCoords().y() - 1), Cell::DOT);
                }

                field->setCellState(QPoint(shotedShip->getCoords().x() - 1, shotedShip->getCoords().y()), Cell::DOT);
                field->setCellState(QPoint(shotedShip->getCoords().x() + shotedShip->getWeight(), shotedShip->getCoords().y()), Cell::DOT);

            } else {
                for (int i {0}; i < shotedShip->getWeight(); i++) {
                    field->setCellState(QPoint(shotedShip->getCoords().x(), shotedShip->getCoords().y() + i), Cell::DEAD);
                }

                // расстановка точек вокруг мертвого корабля по вертикали
                for (int i {-1}; i < shotedShip->getWeight() + 1; i++) {
                    field->setCellState(QPoint(shotedShip->getCoords().x() + 1, shotedShip->getCoords().y() + i), Cell::DOT);
                    field->setCellState(QPoint(shotedShip->getCoords().x() - 1, shotedShip->getCoords().y() + i), Cell::DOT);
                }

                field->setCellState(QPoint(shotedShip->getCoords().x(), shotedShip->getCoords().y() - 1), Cell::DOT);
                field->setCellState(QPoint(shotedShip->getCoords().x(), shotedShip->getCoords().y() + shotedShip->getWeight()), Cell::DOT);
            }

            qDebug() << "Убили" << shotedShip->getWeight() << "палубник";

        }
    }
}

void GameController::playerShot(QPoint point) {
    takeShot(player, bot, point);
}

int GameController::checkForGameOver() {
    Field* playerBoard = player->getField();
    Field* botBoard = bot->getField();
    QVector<Ship*> botFlot = botBoard->getFlot();
    QVector<Ship*> playerFlot = playerBoard->getFlot();

    int playerSummuryHelth = 0;

    for (Ship* ship : playerFlot) {
        playerSummuryHelth += ship->getHealth();
    }

    if (playerSummuryHelth == 0) {
        return 1; // победа бота
    }

    int botSummuryHelth = 0;
    for (Ship* ship : botFlot) {
        botSummuryHelth += ship->getHealth();
    }

    if (botSummuryHelth == 0) {
        return 2; // победа игрока
    }

    // qDebug() << "Суммарное здоровье игрока:" << playerSummuryHelth;
    // qDebug() << "Суммарное здоровье бота:" << botSummuryHelth;

    return 0;
}

void GameController::setGameState(GameState newState) {
    gameState = newState;
}

void GameController::swapGameState() {
    if (getGameState() == GameState::ENEMY_TURN)
        setGameState(GameState::PLAYER_TURN);
    else if (getGameState() == GameState::PLAYER_TURN){
        setGameState(GameState::ENEMY_TURN);
    }
}

void GameController::botShot() {
    takeShot(bot, player, QPoint(-1, -1));

    sleep(1);
}
