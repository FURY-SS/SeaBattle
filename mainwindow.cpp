#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setFixedSize(830, 495);

    gameController = new GameController();

    qDebug() << "Главное окно создано, контроллер инициализирован";

    QPalette pal;
    pal.setBrush(QPalette::Active, QPalette::Window, QBrush(QPixmap(":/field.png")));
    this->setPalette(pal);

    gameController->infoLabel = new QLabel(this);
    gameController->infoLabel->move(330, 420);
    gameController->infoLabel->setText("Расставьте корабли!");
    gameController->infoLabel->setFixedSize(170, 31);
    gameController->infoLabel->setStyleSheet("font-weight: bold; border-style: outset; border-width: 3px; border-radius: 14px;");
    gameController->infoLabel->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow() {
    delete gameController;
}

QPoint MainWindow::getCoords(int x, int y, int fieldX, int fieldY) {
    QPoint res(-1, -1);
    if (x < fieldX || x > (fieldX + 308) || y < fieldY || y > (fieldY + 308)) {
        return res;
    }

    double cfx = 1.0 * 308 / 10.0;
    double cfy = 1.0 * 308 / 10.0;
    res.setX(1.0 * (x - fieldX) / cfx);
    res.setY(1.0 * (y - fieldY) / cfy);

    return res;
}
