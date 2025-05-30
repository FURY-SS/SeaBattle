#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamecontroller.h"
#include <QImage>
#include <QMouseEvent>
#include <QApplication>
#include "sizefields.h"
#include <QDialog>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QPoint getCoordsPlayer(int x, int y);
    QPoint getCoords(int x, int y, int fieldX, int fieldY);

private:
    GameController *gameController;
    QPushButton* rulesButton;

private slots:
    void showRulesDialog();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
