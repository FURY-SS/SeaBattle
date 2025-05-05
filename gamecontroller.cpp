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
