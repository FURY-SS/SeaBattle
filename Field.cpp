#include "Field.h"

Field::Field() {
    cells.fill(EMPTY, 100);
}

void Field::addShip(Ship *ship) {
    flot.push_back(ship);
}

void Field::setCellState(QPoint point, Cell state) {
    if (point.x() < BOARD_SIZE && point.x() >= 0 && point.y() < BOARD_SIZE && point.y() >= 0) {
        cells[point.x() + BOARD_SIZE * point.y()] = state;
    }
}

Cell Field::getCellState(QPoint point) {
    if (point.x() > 9 || point.y() > 9 || point.x() < 0 || point.y() < 0) {
        return Cell::EMPTY;
    }

    return cells[point.x() + BOARD_SIZE * point.y()];
}

void Field::printFieldStates() {
    // Вывод игрового поля в виде матрицы
    for (int i = 0; i < BOARD_SIZE; i++) {
        QString str = "";
        for (int j = 0; j < BOARD_SIZE; j++) {
            str += QString::number(cells[i * BOARD_SIZE + j]) + " ";
        }
        qDebug() << str;
    }
    qDebug() << "\n";
}

QVector<Cell> Field::getCells() {
    return cells;
}

QVector<Ship *> Field::getFlot() {
    return flot;
}

void Field::prettyPrintFlot() {
    for (Ship* ship : flot) {
        qDebug() << "w:" << ship->getWeight() << ", " << ship->getCoords();
    }
}

void Field::clear() {
    for (Cell &cell : cells) {
        cell = Cell::EMPTY;
    }
}

Ship *Field::getShipByCell(QPoint point) {
    // Проверка: если переданная клетка не содержит корабля, вывод сообщения
    if (getCellState(point) != Cell::SHIP) {
        qDebug() << "В функцию getShipByCell передана клетка без корабля!";
        return nullptr;
    }

    // Проверка на то, что мы как раз тыкнули на нос корабля
    for (Ship* ship : flot) {
        if (ship->getCoords() == point) {
            return ship;
        }
    }

    // Если корабль расположен горизонтально: ищем нос слева
    if (getCellState(QPoint(point.x() - 1, point.y())) == Cell::SHIP || getCellState(QPoint(point.x() - 1, point.y())) == Cell::DAMAGED) {
        while (true) {
            point = QPoint(point.x() - 1, point.y());
            for (Ship* ship : flot) {
                if (ship->getCoords() == point) {
                    return ship;
                }
            }
        }
    } else {
        // Вертикальное расположение: ищем нос сверху
        while (true) {
            point = QPoint(point.x(), point.y() - 1);
            for (Ship* ship : flot) {
                if (ship->getCoords() == point) {
                    return ship;
                }
            }
        }
    }

    qDebug() << "Не нашел корабль..";
    return nullptr;
}
