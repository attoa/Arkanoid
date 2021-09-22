#include "mainwindow.h"
#include "ui_mainwindow.h"

#define b_x (ball->x())
#define b_y (ball->y())
#define b_d (ball->getDiameter())
#define p_w (platform->getWidth())
#define p_h (platform->getHeight())
#define bl_x (block->x())
#define bl_y (block->y())
#define bl_w (Block::getWidth())
#define bl_h (Block::getHeight())

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->labelNextLevel->setVisible(false);

    //Получение размеров виджета
    h = ui->graphicsView->height();
    w = ui->graphicsView->width();

    //Создание сцены
    scene = new Scene(this);
    scene->setSceneRect(0, 0, w-3, h-3);

    //Загрузка изображения фона виджета
    backImage = QImage(":/images/images/background.jpg");
    backImage = backImage.scaled(w, h);

    //Настройка виджета graphicsView
    ui->graphicsView->setBackgroundBrush(backImage);    //Установка фона
    ui->graphicsView->setScene(scene);                  //Установка графической сцены
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);        //Установка сглаживания
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); //Установка кэша фона

    //Добавление линий-ограничителей игровой области на сцене
    scene->addLine(0, 0, w, 0, QPen(Qt::blue));     //сверху
    scene->addLine(0, 0, 0, h, QPen(Qt::blue));     //слева
    scene->addLine(w-2, 0, w-2, h, QPen(Qt::blue)); //справа

    //Создание Шара и Платформы
    ball = new Ball();
    platform = new Platform(0+2, w-2, 100);

    //Добавление Шара и Платформы на сцену
    scene->addItem(ball);
    scene->addItem(platform);

    //Инициализация таймера
    timer = new QTimer();

    //Подключение сигнала таймера
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTicTimer);

    //Создание Уровней
    for (int i = 0; i < LEVELSCOUNT; i++)
        levels[i] = new Level(i + 1);

    level = levels[0];
    bestscore = 0;
    changeScore(false);
    prepareNewGame();

    scene->update();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ball;
    delete platform;
    for (Block* block : blocks) delete block;
    for (Level* level : levels) delete level;
    delete scene;
    delete timer;
}

void MainWindow::slotTicTimer()
{
    //Отражение от левой или правой границы
    if (b_x <= 2 || b_x >= w - b_d - 2)
        ball->invertDx();

    //Отражение от верхней границы
    if (b_y <= 2)
        ball->invertDy();

    //Уход за нижнюю границу
    if (b_y > h)
    {
        stopGame();
        return;
    }

    //Перебор объектов, пересекаемых шаром на сцене
    for (QGraphicsItem* item : ball->collidingItems())
    {
        //Пересечение с объектом типа платформа
        if (item == platform && b_y + b_d - ball->dy <= h - p_h)
        {
            ball->invertDy();
            break;
        }

        //Пересечение с объектом типа блок
        if (Block* block = dynamic_cast<Block*>(item))
        {
            //Величины пересечений сторон блока
            float up = (b_y + b_d) - bl_y, down = (bl_y + bl_h) - b_y,
                right = (bl_x + bl_w) - b_x, left = (b_x + b_d) - bl_x;

            float y = qMin(up, down), x = qMin(right, left);

            if (y >= x) ball->invertDx();
            if (y <= x) ball->invertDy();

            //Увеличение счета
            changeScore(true);

            //Удаление блока
            scene->removeItem(block);   //со сцены
            blocks.removeOne(block);    //из списка
            delete block;               //из памяти

            //Переход на следующий уровень если блоков больше нет
            if (blocks.size() == 0)
            {
                nextLevel();
                return;
            }
            break;
        }
    }

    ball->move();
}

void MainWindow::prepareNewGame()
{
    //Установка доступности виджетов
    ui->labelGameOver->setVisible(false);
    ui->spinBoxLevel->setValue(level->number);
    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    platform->setWidth(level->platformWidth);
    loadMap();

    //Установка Шара и Платформы в исходную позицию
    ball->setPos((w - b_d)/2, h - b_d - p_h - 10);
    platform->setPos((w - p_w)/2, h - p_h);

    ball->dy = (qrand() % 10 + 20)/10.0f;

    platform->isMovable = false;
}

void MainWindow::startGame()
{
    timer->start(level->speed);

    platform->isMovable = true;

    //Установка доступности виджетов
    ui->startButton->setEnabled(false);
    ui->spinBoxLevel->setEnabled(false);
    ui->pauseButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
}

void MainWindow::stopGame()
{
    timer->stop();

    platform->isMovable = false;

    if (score > bestscore)
    {
        bestscore = score;
        ui->labelBestScore->setText(QString::number(bestscore));
    }

    //Установка доступности виджетов
    ui->labelGameOver->setVisible(true);
    ui->startButton->setEnabled(true);
    ui->spinBoxLevel->setEnabled(true);
    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
}

void MainWindow::nextLevel()
{
    if (level->number == LEVELSCOUNT)
    {
        stopGame();
        return;
    }

    timer->stop();

    level = levels[level->number+1-1];
    prepareNewGame();
    ui->labelNextLevel->setVisible(true);

    //Ожидание 1.5 сек
    QTimer::singleShot(1500, NULL, [this]() {
        ui->labelNextLevel->setVisible(false);
        startGame();
    });
}

void MainWindow::loadMap()
{
    //Удаление существующих блоков
    for (Block* block : blocks)
    {
        scene->removeItem(block);
        delete block;
    }
    blocks.clear();

    //Создание блоков по карте уровня
    for (int i = 0; i < BLOCKCOUNTY; i++)
    {
        for (int j = 0; j < BLOCKCOUNTX; j++)
        {
            auto el = level->map[i][j]; //Текущий элемент массива

            if (el != empty)
            {
                Block *block;   //Создаваемый блок

                switch(el) {
                case red:
                    block = new Block(Qt::red);
                    break;

                case green:
                    block = new Block(Qt::green);
                    break;

                case blue:
                    block = new Block(Qt::blue);
                    break;
                }

                block->setPos(BLOCKINITX + bl_w * j, BLOCKINITY + bl_h * i);
                scene->addItem(block);
                blocks.push_back(block);
            }
        }
    }
}

void MainWindow::changeScore(bool increase)
{
    increase ? score += 100 : score = 0;

    ui->labelScore->setText(QString::number(score));
}

void MainWindow::on_startButton_clicked()
{
    changeScore(false);
    prepareNewGame();
    startGame();
}

void MainWindow::on_pauseButton_clicked()
{
    if (ui->pauseButton->text() == "Пауза")
    {
        ui->pauseButton->setText("Продолжить");
        timer->stop();
    }
    else
    {
        ui->pauseButton->setText("Пауза");
        timer->start(level->speed);
    }
}

void MainWindow::on_stopButton_clicked()
{
    stopGame();
    ui->pauseButton->setText("Пауза");
}

void MainWindow::on_spinBoxLevel_valueChanged(int arg1)
{
    if (arg1 >= 1 && arg1 <= LEVELSCOUNT)
    {
        level = levels[arg1 - 1];
        prepareNewGame();
    }
}
