#include "mainwindow.h"
#include <QApplication>
#include "Field.h"
#include "gamecontroller.h"
#include <QRandomGenerator>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    GameController controller;

    qDebug() << "Изначальное количество клеток с кораблями у игрока:" << controller.getPlayerShipCellsCount();
    qDebug() << "Изначальное количество клеток с кораблями у бота:" << controller.getBotShipCellsCount();

    QPoint testPoint(3, 4);
    if (controller.isPlayerEmptyCell(testPoint)) {
        controller.setPlayerCellState(testPoint, static_cast<int>(Cell::SHIP));
        qDebug() << "Клетка (3,4) была пустой. Установили туда корабль.";
    } else {
        qDebug() << "Клетка (3,4) уже занята.";
    }

    Cell cellState = controller.getPlayerCellState(testPoint);
    qDebug() << "Состояние клетки (3,4):" << static_cast<int>(cellState);

    qDebug() << "\nВывод поля игрока:";
    controller.printPlayerAllCellStates();

    return a.exec();
}
