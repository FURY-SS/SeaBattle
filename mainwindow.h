#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Images.h"
#include "Field.h"
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

// Состояния игры
enum State {
    ST_PLACING_SHIPS,
    ST_WAITING_STEP,
    ST_MAKING_STEP
};

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    Images *pictures;
    Field *myField, *enemyField;
    State state;
};
#endif // MAINWINDOW_H
