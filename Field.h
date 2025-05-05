#ifndef FIELD_H
#define FIELD_H

#include <QVector>
#include <QImage>
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <QString>
#include "Images.h"
#include "ship.h"

// Состояния клетки поля
enum Cell {
    EMPTY,
    DOT,
    SHIP,
    DEAD,
    DAMAGED
};

class Field {
    QVector<Cell> cells;
    QVector<Ship*> flot;

public:
    Field();

    void addShip(Ship* ship);
    void setCellState(QPoint point, Cell state);
    Cell getCellState(QPoint point);
    void printBoardStates();

    QVector<Cell> getCells();

    QVector<Ship *> getFlot();
    void prettyPrintFlot();
    void clear();

    Ship *getShipByCell(QPoint point);
};

#endif // FIELD_H
