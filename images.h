#ifndef IMAGES_H
#define IMAGES_H

#include <QMap>
#include <QImage>
#include <QString>

class Images
{

public:
    void load();
    QImage& get(const QString& imgName);

private:
    QMap<QString,QImage> images;
};

#endif // IMAGES_H
