#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    pictures = new Images;
    pictures->load();

    myField = new Field(pictures,42,39,216,217);
    enemyField = new Field(pictures,322,39,214,217);

    myField->redraw();
    enemyField->redraw();

    state=ST_PLACING_SHIPS;
}

MainWindow::~MainWindow() {
    delete pictures;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0,this->menuBar()->geometry().height(), pictures->get("field"));
    painter.drawImage(myField->getX(),this->menuBar()->geometry().height()+myField->getY(), myField->getImage());
    painter.drawImage(enemyField->getX(),this->menuBar()->geometry().height()+enemyField->getY(), enemyField->getImage());
}

void MainWindow::mousePressEvent(QMouseEvent * ev) {
    QPoint pos=ev->pos();
    pos.setY(pos.y()-this->menuBar()->geometry().height());

    if (state==ST_PLACING_SHIPS) {
        QPoint point=myField->getCoord(pos.x(),pos.y());
        if (point.x() == -1) {
            return;
        }

        qDebug() << "Ship at" << point.x() << point.y();
        myField->setCell(point.x(),point.y(),CL_SHIP);
        myField->redraw();
        this->update();

    } else if (state==ST_MAKING_STEP) {
        QPoint point=enemyField->getCoord(pos.x(),pos.y());
        if (point.x() == -1) {
            return;
        }

        qDebug() << "Going to" << point.x() << point.y();
        enemyField->setCell(point.x(),point.y(),CL_DOT);
        enemyField->redraw();
        this->update();
    }
}

