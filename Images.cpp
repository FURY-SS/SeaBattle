#include "Images.h"

void Images::load() {
    images.insert("field",QImage(":/field.png"));
    images.insert("dot",QImage(":/dot.png"));
    images.insert("full",QImage(":/full.png"));
    images.insert("half",QImage(":/half.png"));

}

QImage& Images::get(const QString& imgName) {
    return images[imgName];
}
