#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Images.h"
#include "Field.h"
#include <QMouseEvent>
#include "player.h"

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

    Ui::MainWindow *ui;
    Images *pictures;
    Field *myField, *enemyField;
    State state;
    HumanPlayer *humanPlayer;
    AIPlayer *aiPlayer;

    int shipsToPlace[4]; // Количество кораблей каждого типа
    int currentShipSize; // Размер текущего размещаемого корабля
    bool isHorizontal;   // Ориентация текущего корабля

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override; //обработчик нажатия клавиш

private:
    bool canPlaceShip(int x, int y, int size, bool horizontal); // Проверка возможности размещения корабля
    void placeShip(int x, int y, int size, bool horizontal);    // Размещение корабля на поле
    void updateShipsToPlace();                                  // Обновление информации о кораблях для размещения
    void startGame();                                           // Начало игры после размещения всех кораблей
};

#endif // MAINWINDOW_H
