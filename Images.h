#ifndef IMAGES_H
#define IMAGES_H

#include <QMap>
#include <QImage>
#include <QString>

class Images {
    QMap<QString,QImage> images;

public:
    void load();
    QImage& get(const QString& imgName);
};

#endif // IMAGES_H
