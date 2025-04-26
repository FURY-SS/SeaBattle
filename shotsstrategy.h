#ifndef SHOTSSTRATEGY_H
#define SHOTSSTRATEGY_H

#include <QPoint>
#include "Field.h"

class ShotsStrategy {
public:
    ShotsStrategy(Field* field) : field(field) {}
    virtual ~ShotsStrategy() {}
    virtual QPoint makeShot(QPoint point = QPoint(-1, -1)) = 0;

protected:
    Field* field;
};

class ManualShotStrategy : public ShotsStrategy {
public:
    ManualShotStrategy(Field* field) : ShotsStrategy(field) {}
    QPoint makeShot(QPoint point) override;
};

class RandomShotStrategy : public ShotsStrategy {
public:
    RandomShotStrategy(Field* field) : ShotsStrategy(field) {}
    QPoint makeShot(QPoint point) override;
};
#endif // SHOTSSTRATEGY_H
