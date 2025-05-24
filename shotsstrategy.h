#ifndef SHOTSSTRATEGY_H
#define SHOTSSTRATEGY_H

#include <QPoint>
#include "sizefields.h"

class ShotsStrategy {
public:

    virtual QPoint shot(QPoint point = QPoint(0, 0)) = 0;
};

class ManualShotStrategy : public ShotsStrategy {
public:
    QPoint shot(QPoint point = QPoint(0, 0));
};

class RandomShotStrategy : public ShotsStrategy {
public:
    QPoint shot(QPoint point = QPoint(0, 0));
};

#endif // SHOTSSTRATEGY_H
