#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    pictures = new Images;
    pictures->load();

    myField = new Field(pictures,42,39,216,217);
    enemyField = new Field(pictures,330,46,216,217);

    humanPlayer = new HumanPlayer(myField);
    aiPlayer = new AIPlayer(myField);

    gameController = new GameController(humanPlayer, aiPlayer);

    // Инициализация количества кораблей для размещения
    shipsToPlace[0] = 4;
    shipsToPlace[1] = 3;
    shipsToPlace[2] = 2;
    shipsToPlace[3] = 1;

    currentShipSize = 4; // Начинаем с самого большого корабля
    isHorizontal = true; // По умолчанию горизонтальная ориентация

    state = SHIPS_PLACING;

    myField->redraw();
    enemyField->redraw();

    updateShipsToPlace();
}

MainWindow::~MainWindow() {
    delete pictures;
    delete ui;
    delete humanPlayer;
    delete aiPlayer;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(0, this->menuBar()->geometry().height(), pictures->get("field"));
    painter.drawImage(myField->getX(), this->menuBar()->geometry().height() + myField->getY(), myField->getImage());
    painter.drawImage(enemyField->getX(), this->menuBar()->geometry().height() + enemyField->getY(), enemyField->getImage());
}

void MainWindow::mousePressEvent(QMouseEvent *ev) {
    QPoint pos = ev->pos();
    pos.setY(pos.y() - this->menuBar()->geometry().height());

    if (state == SHIPS_PLACING) {
        QPoint point = myField->getCoord(pos.x(), pos.y());
        if (point.x() == -1) return;

        if (canPlaceShip(point.x(), point.y(), currentShipSize, isHorizontal)) {
            // Демонстрация фабричного метода
            Ship* newShip = humanPlayer->createShip(currentShipSize);
            if (!newShip) {
                QMessageBox::warning(this, "Ошибка", "Не удалось создать корабль");
                return;
            }

            // Устанавливаем параметры корабля
            newShip->setCoords(point);
            newShip->setOrientation(isHorizontal);

            // Размещаем на поле
            placeShip(point.x(), point.y(), currentShipSize, isHorizontal);

            // Выводим информацию о созданном корабле
            QString shipInfo = QString("Создан корабль: %1-палубный, ориентация %2")
                                   .arg(currentShipSize)
                                   .arg(isHorizontal ? "горизонтальная" : "вертикальная");
            ui->statusbar->showMessage(shipInfo, 3000); // Показываем 3 секунды

            // Обновляем интерфейс
            shipsToPlace[currentShipSize-1]--;
            updateShipsToPlace();

            // Ищем следующий корабль
            currentShipSize = 0;
            for (int i = 3; i >= 0; --i) {
                if (shipsToPlace[i] > 0) {
                    currentShipSize = i+1;
                    break;
                }
            }

            if (currentShipSize == 0) {
                startGame();
            }
        } else {
            QMessageBox::warning(this, "Ошибка", "Невозможно разместить корабль здесь!");
        }

    } else if (state == PLAYER_TURN) {
        QPoint point = enemyField->getCoord(pos.x(), pos.y());
        if (point.x() == -1){
            return;
        }

        // Проверяем, можно ли сделать выстрел в эту клетку
        if (enemyField->getCell(point.x(), point.y()) == CL_CLEAR) {
            // Просто отмечаем выстрел (без логики противника)
            enemyField->setCell(point.x(), point.y(), CL_DOT);
            enemyField->redraw();
            this->update();

            // переход хода к противнику здесь
            //state = ST_WAITING_STEP;
        } else {
            QMessageBox::information(this, "Информация", "Вы уже стреляли в эту клетку!");
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // Обработка смены ориентации корабля при нажатии пробела
    if (event->key() == Qt::Key_Space && state == SHIPS_PLACING) {
        isHorizontal = !isHorizontal;
        QMessageBox::information(this, "Информация", isHorizontal ? "Горизонтальная ориентация" : "Вертикальная ориентация");
    }
}

bool MainWindow::canPlaceShip(int x, int y, int size, bool horizontal) {
    // Проверяем, что корабль помещается в поле
    if (horizontal) {
        if (x + size > 10) {
            return false;
        }
    } else {
        if (y + size > 10) {
            return false;
        }
    }

    // Проверяем соседние клетки на наличие других кораблей
    for (int i = -1; i <= (horizontal ? size : 1); ++i) {
        for (int j = -1; j <= (horizontal ? 1 : size); ++j) {
            int checkX = x + i;
            int checkY = y + j;

            // Проверяем только валидные координаты
            if (checkX >= 0 && checkX < 10 && checkY >= 0 && checkY < 10) {
                // Проверяем, что клетка не занята другим кораблем
                if (myField->getCell(checkX, checkY) == CL_SHIP) {
                    return false;
                }
            }
        }
    }

    return true;
}

void MainWindow::placeShip(int x, int y, int size, bool horizontal) {
    // Размещаем корабль на поле
    for (int i = 0; i < size; ++i) {
        int shipX = horizontal ? x + i : x;
        int shipY = horizontal ? y : y + i;
        myField->setCell(shipX, shipY, CL_SHIP);
    }

    myField->redraw();
    this->update();
}

void MainWindow::updateShipsToPlace() {
    // Обновляем информацию о кораблях для размещения (можно вывести в статусную строку)
    QString status = QString("Разместите корабли: %1x4, %2x3, %3x2, %4x1").arg(shipsToPlace[3]).arg(shipsToPlace[2]).arg(shipsToPlace[1]).arg(shipsToPlace[0]);
    ui->statusbar->showMessage(status);
}

void MainWindow::startGame() {
    state = PLAYER_TURN;
    QMessageBox::information(this, "Начало игры", "Все корабли размещены! Игра начинается.");
    ui->statusbar->showMessage("Ваш ход. Стреляйте по полю противника.");
}
