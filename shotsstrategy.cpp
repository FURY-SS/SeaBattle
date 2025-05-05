#include "shotsstrategy.h"
#include <ctime>
#include <cstdlib>

QPoint ManualShotStrategy::shot(QPoint point) {

    return point;
}

QPoint RandomShotStrategy::shot(QPoint) {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    return QPoint(std::rand() % 10, std::rand() % 10);
}
