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

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // обработка нажатия правой кнопкой мыши
    if (event->button() == Qt::RightButton) {
        QPoint pos = event->pos();

        qDebug() << "Mouse click at (" << pos.x() << "," << pos.y() << ")";

        qDebug() << "\nПоле бота:";
        gameController->printBotAllCellStates();

    }

    // нажатие левой кнопкой мыши
    else if (event->button() == Qt::LeftButton) {

        // если состояние = расстановка кораблей
        if (gameController->getGameState() == GameState::SHIPS_PLACING) {
            QPointF pos = event->position();

            if (pos.x() >= 62 && pos.x() <= 308 + 62
                && pos.y() >= 62 && pos.y() <= 308 + 62) {

                QPoint qp = getCoords(pos.x(), pos.y(), 62, 62);

                if (qp.x() == 10)
                    qp.setX(9);
                if (qp.y() == 10)
                    qp.setY(9);

                if (gameController->isPlayerEmptyCell(qp)) {
                    if (gameController->getPlayerShipCellsCount() < 20) {
                        gameController->setPlayerCellState(qp, 2);

                        if (gameController->checkPlayerShipPlacement()) {
                            gameController->infoLabel->setText("Начать - ПРОБЕЛ");
                        }
                    }
                } else {
                    gameController->setPlayerCellState(qp, 0);
                    gameController->infoLabel->setText("Расставьте корабли!");
                }


                update();

            }
        } else if (gameController->getGameState() == GameState::PLAYER_TURN) {
            QPointF pos = event->position();

            if (pos.x() >= 462 && pos.x() <= 308 + 462
                && pos.y() >= 62 && pos.y() <= 308 + 62) {
                QPoint qp = getCoords(pos.x(), pos.y(), 462, 62);

                if (qp.x() == 10)
                    qp.setX(9);
                if (qp.y() == 10)
                    qp.setY(9);

                gameController->playerShot(qp);
                repaint();
                QApplication::processEvents();

                // проверка на завершение игры

                int gO_status = gameController->checkForGameOver();
                if (gameController->checkForGameOver() != 0) {
                    if (gO_status == 2) {
                        gameController->setGameState(GameState::GAMEOVER);
                        gameController->infoLabel->setText("Вы Победили!");
                    } else {
                        gameController->setGameState(GameState::GAMEOVER);
                        gameController->infoLabel->setText("Вы Проиграли!");
                    }
                }

                while (gameController->getGameState() == GameState::ENEMY_TURN) {
                    // ход бота
                    gameController->botShot();
                    repaint();
                    QApplication::processEvents();

                    // проверка на завершение игры
                    int gO_status = gameController->checkForGameOver();
                    if (gameController->checkForGameOver() != 0) {
                        if (gO_status == 2) {
                            gameController->setGameState(GameState::GAMEOVER);
                            gameController->infoLabel->setText("Вы Победили!");
                        } else {
                            gameController->setGameState(GameState::GAMEOVER);
                            gameController->infoLabel->setText("Вы Проиграли!");
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    QVector<Cell> currentCellsState = gameController->getPlayerAllCells();

    // отрисовка поля игрока
    for (int i {0}; i < currentCellsState.size(); i++) {
        if (currentCellsState[i] == Cell::SHIP) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(62 + (x * 31));
                drawPoint.setY(62 + (y * 31));
            } else {
                drawPoint.setX(216 + ((x - 5) * 31));
                drawPoint.setY(216 + ((y - 5) * 31));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/full.png"));
        } else if (currentCellsState[i] == Cell::DAMAGED) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(62 + (x * 31));
                drawPoint.setY(62 + (y * 31));
            } else {
                drawPoint.setX(216 + ((x - 5) * 31));
                drawPoint.setY(216 + ((y - 5) * 31));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/half.png"));
        } else if (currentCellsState[i] == Cell::DEAD) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(62 + (x * 31));
                drawPoint.setY(62 + (y * 31));
            } else {
                drawPoint.setX(216 + ((x - 5) * 31));
                drawPoint.setY(216 + ((y - 5) * 31));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/full.png"));
        } else if (currentCellsState[i] == Cell::DOT) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(62 + (x * 31));
                drawPoint.setY(62 + (y * 31));
            } else {
                drawPoint.setX(216 + ((x - 5) * 31));
                drawPoint.setY(216 + ((y - 5) * 31));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/dot.png"));
        }
    }

    //Отрисовка поля бота, дописать...
}
