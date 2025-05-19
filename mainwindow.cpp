#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setFixedSize(830, 495);

    gameController = new GameController();

    qDebug() << "Главное окно создано, контроллер инициализирован";

    QPalette pal;
    pal.setBrush(QPalette::Active, QPalette::Window, QBrush(QPixmap(":/field.png")));
    this->setPalette(pal);

    gameController->infoLabel = new QLabel(this);
    gameController->infoLabel->move(330, 400);
    gameController->infoLabel->setText("Расставьте корабли!");
    gameController->infoLabel->setFixedSize(170, 31);
    gameController->infoLabel->setStyleSheet("font-family: Arial; font-size: 14px; font-weight: bold; color: black; background-color: white; border: 3px solid black; border-radius: 14px; padding: 4px 10px;");
    gameController->infoLabel->setAlignment(Qt::AlignCenter);

    rulesButton = new QPushButton("Правила игры", this);
    rulesButton->setFocusPolicy(Qt::NoFocus);
    rulesButton->setGeometry(330, 440, 170, 31);
    rulesButton->setStyleSheet("font-family: Arial; font-size: 14px; font-weight: bold; color: black; background-color: white; border: 3px solid black; border-radius: 14px; padding: 4px 10px;");
    connect(rulesButton, &QPushButton::clicked, this, &MainWindow::showRulesDialog);
}

MainWindow::~MainWindow() {
    delete gameController;
}

QPoint MainWindow::getCoords(int x, int y, int fieldX, int fieldY) {
    QPoint res(-1, -1);
    if (x < fieldX || x > (fieldX + FIELD_WIDTH) || y < fieldY || y > (fieldY + FIELD_HEIGHT)) {
        return res;
    }

    double cfx = 1.0 * FIELD_WIDTH / 10.0;
    double cfy = 1.0 * FIELD_HEIGHT / 10.0;
    res.setX(1.0 * (x - fieldX) / cfx);
    res.setY(1.0 * (y - fieldY) / cfy);

    return res;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    // обработка нажатия правой кнопкой мыши
    if (event->button() == Qt::RightButton) {
        QPoint pos = event->pos();

        qDebug() << "Mouse click at (" << pos.x() << "," << pos.y() << ")";

        //qDebug() << "\nПоле бота:";
        //gameController->printBotAllCellStates();

    }

    // нажатие левой кнопкой мыши
    else if (event->button() == Qt::LeftButton) {

        // если состояние = расстановка кораблей
        if (gameController->getGameState() == GameState::SHIPS_PLACING) {
            QPointF pos = event->position();

            if (pos.x() >= MYFIELD_X && pos.x() <= FIELD_WIDTH + MYFIELD_X && pos.y() >= MYFIELD_Y && pos.y() <= FIELD_HEIGHT + MYFIELD_Y) {

                QPoint qp = getCoords(pos.x(), pos.y(), MYFIELD_X, MYFIELD_Y);

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

            if (pos.x() >= ENEMYFIELD_X && pos.x() <= FIELD_WIDTH + ENEMYFIELD_X && pos.y() >= ENEMYFIELD_Y && pos.y() <= FIELD_HEIGHT + ENEMYFIELD_Y) {
                QPoint qp = getCoords(pos.x(), pos.y(), ENEMYFIELD_X, ENEMYFIELD_Y);

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
                drawPoint.setX(MYFIELD_X + (x * CELL_SIZE_X));
                drawPoint.setY(MYFIELD_Y + (y * CELL_SIZE_Y));
            } else {
                drawPoint.setX(MYFIELD_HALF_X + ((x - 5) * CELL_SIZE_X));
                drawPoint.setY(MYFIELD_HALF_Y + ((y - 5) * CELL_SIZE_Y));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/full.png"));
        } else if (currentCellsState[i] == Cell::DAMAGED) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(MYFIELD_X + (x * CELL_SIZE_X));
                drawPoint.setY(MYFIELD_Y + (y * CELL_SIZE_Y));
            } else {
                drawPoint.setX(MYFIELD_HALF_X + ((x - 5) * CELL_SIZE_X));
                drawPoint.setY(MYFIELD_HALF_Y + ((y - 5) * CELL_SIZE_Y));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/half_r.png"));
        } else if (currentCellsState[i] == Cell::DEAD) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(MYFIELD_X + (x * CELL_SIZE_X));
                drawPoint.setY(MYFIELD_Y + (y * CELL_SIZE_Y));
            } else {
                drawPoint.setX(MYFIELD_HALF_X + ((x - 5) * CELL_SIZE_X));
                drawPoint.setY(MYFIELD_HALF_Y + ((y - 5) * CELL_SIZE_Y));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/full_r.png"));
        } else if (currentCellsState[i] == Cell::DOT) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(MYFIELD_X + (x * CELL_SIZE_X));
                drawPoint.setY(MYFIELD_Y + (y * CELL_SIZE_Y));
            } else {
                drawPoint.setX(MYFIELD_HALF_X + ((x - 5) * CELL_SIZE_X));
                drawPoint.setY(MYFIELD_HALF_Y + ((y - 5) * CELL_SIZE_Y));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/dot.png"));
        }
    }

    QVector<Cell> currentCellsStateBot = gameController->getBotAllCells();

    // отрисовка поля бота
    for (int i {0}; i < currentCellsStateBot.size(); i++) {
        if (currentCellsStateBot[i] == Cell::DOT) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(ENEMYFIELD_X + (x * CELL_SIZE_X));
                drawPoint.setY(ENEMYFIELD_Y + (y * CELL_SIZE_Y));
            } else {
                drawPoint.setX(ENEMYFIELD_HALF_X + ((x - 5) * CELL_SIZE_X));
                drawPoint.setY(ENEMYFIELD_HALF_Y + ((y - 5) * CELL_SIZE_Y));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/dot.png"));
        } else if (currentCellsStateBot[i] == Cell::DAMAGED) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(ENEMYFIELD_X + (x * CELL_SIZE_X));
                drawPoint.setY(ENEMYFIELD_Y + (y * CELL_SIZE_Y));
            } else {
                drawPoint.setX(ENEMYFIELD_HALF_X + ((x - 5) * CELL_SIZE_X));
                drawPoint.setY(ENEMYFIELD_HALF_Y + ((y - 5) * CELL_SIZE_Y));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/half.png"));
        } else if (currentCellsStateBot[i] == Cell::DEAD) {
            QPoint drawPoint;

            int x = i % 10;
            int y = i / 10;

            if (x < 5 && y < 5) {
                drawPoint.setX(ENEMYFIELD_X + (x * CELL_SIZE_X));
                drawPoint.setY(ENEMYFIELD_Y + (y * CELL_SIZE_Y));
            } else {
                drawPoint.setX(ENEMYFIELD_HALF_X + ((x - 5) * CELL_SIZE_X));
                drawPoint.setY(ENEMYFIELD_HALF_Y + ((y - 5) * CELL_SIZE_Y));
            }

            painter.drawPixmap(drawPoint, QPixmap(":/full.png"));
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (gameController->getGameState() == GameState::SHIPS_PLACING) {
        if (event->key() == Qt::Key_Space) {
            if (gameController->checkPlayerShipPlacement()) {

                // синхронизация кораблей и клеток
                gameController->syncPlayerShipsCells();

                // расстановка кораблей ботом
                gameController->botRandomShipsPlacing();

                // смена состояния на ХОД ИГРОКА
                gameController->setGameState(GameState::PLAYER_TURN);

                // смена надписи
                gameController->infoLabel->setText("Твой Ход!");
            }
        }
    }
}

void MainWindow::showRulesDialog() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Правила игры");
    dialog->setFixedSize(500, 600);
    dialog->setStyleSheet("background-color: white;");

    QLabel* textLabel = new QLabel(dialog);

    textLabel->setText(
        "<div align='center'>"
        "<span style='font-size:16px; font-weight:bold;'>Правила игры «Морской бой»</span><br><br>"
        "<span style='font-size:13px;'>"
        "Каждый игрок размещает на своём поле флот из 10 кораблей:<br>"
        "- 1 четырёхпалубный<br>"
        "- 2 трёхпалубных<br>"
        "- 3 двухпалубных<br>"
        "- 4 однопалубных<br><br>"
        "Корабли не могут касаться друг друга, даже по диагонали.<br>"
        "Цель — первым уничтожить весь флот противника.<br>"
        "Игроки стреляют по очереди. Попадание даёт ещё один ход.<br>"
        "После уничтожения корабля вокруг него автоматически ставятся точки.<br>"
        "Следи за информационным окном выше правил.<br><br>"
        "Пример расстановки приведён ниже:"
        "</span>"
        "</div>"
        );

    textLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    textLabel->setGeometry(20, 10, 460, 280);
    textLabel->setWordWrap(true);

    QLabel* imageLabel = new QLabel(dialog);
    imageLabel->setPixmap(QPixmap(":/rules.png").scaled(460, 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setGeometry(20, 300, 460, 260);
    imageLabel->setAlignment(Qt::AlignCenter);

    dialog->exec();
}
