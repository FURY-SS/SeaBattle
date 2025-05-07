#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    controller = new GameController();
    setupUI();
    drawFields();
}

MainWindow::~MainWindow() {
    delete controller;
    delete ui;
}

void MainWindow::setupUI() {}

void MainWindow::drawFields() {
    // выведем состояние поля в консоль
    controller->printPlayerAllCellStates();
    controller->printBotAllCellStates();
}
