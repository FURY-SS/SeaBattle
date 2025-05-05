#include "mainwindow.h"
#include <QApplication>
#include "Field.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    Field field;
    // Установим несколько клеток для проверки
    field.setCellState(QPoint(0,0), SHIP);
    field.setCellState(QPoint(1,0), DOT);
    field.setCellState(QPoint(2,0), DAMAGED);

    field.printBoardStates();

    return a.exec();
}
