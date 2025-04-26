#ifndef FIELD_H
#define FIELD_H

#include <QVector>
#include <QImage>
#include <QDebug>
#include <QPainter>
#include <QPoint>
#include <QString>
#include "Images.h"

// Состояния клетки поля
enum Cell {
    CL_CLEAR = 0,
    CL_SHIP,
    CL_DOT,
    CL_HALF
};

class Field {

    QImage *image;
    Images *pictures;
    QVector<Cell> field;
    int left,top,width,height;

public:
    Field(Images* images,int lft, int tp,int wdth,int hght);
    ~Field();

    const QImage& getImage() const;
    void redraw();
    Cell getCell( int x, int y );
    void setCell( int x, int y, Cell cell );

    QString getField();
    QPoint getCoord(int x, int y);

    void clear();
    int getX();
    int getY();
};

#endif // FIELD_H
