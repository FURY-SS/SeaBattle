#include "shotsstrategy.h"

#include "ShotsStrategy.h"
#include <QRandomGenerator>
#include <QDebug>

QPoint ManualShotStrategy::makeShot(QPoint point) {
    if (point.x() == -1 || point.y() == -1) {
        qDebug() << "Invalid shot coordinates";
        return QPoint(-1, -1);
    }
    return point;
}

QPoint RandomShotStrategy::makeShot(QPoint) {
    int x = QRandomGenerator::global()->bounded(10);
    int y = QRandomGenerator::global()->bounded(10);

    // Ensure we don't shoot the same spot twice
    while (field->getCell(x, y) != CL_CLEAR) {
        x = QRandomGenerator::global()->bounded(10);
        y = QRandomGenerator::global()->bounded(10);
    }

    return QPoint(x, y);
}
