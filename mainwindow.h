#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#include "ball.h"
#include "platform.h"
#include "block.h"
#include "level.h"
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Scene *scene;       //Графическая сцена
    QImage backImage;   //Изображение фона сцены
    int h, w;           //Размеры сцены

    Ball *ball;             //Объект шар
    Platform *platform;     //Объект платформа

    QList<Block*> blocks;   //Список блоков на сцене

    Level *level;               //Текущий уровень
    Level *levels[LEVELSCOUNT]; //Массив уровней

    QTimer *timer;  //Таймер контроля столкновений

    int score;      //Счет
    int bestscore;  //Лучший счет

    void prepareNewGame();  //Подготовить новую игру
    void startGame();       //Начать игру
    void stopGame();        //Остановить игру
    void nextLevel();       //Перейти на следующий уровень

    void loadMap();         //Загрузка карты уровня
    void changeScore(bool increase);    //Изменение счета

private slots:
    void slotTicTimer();

    void on_startButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();
    void on_spinBoxLevel_valueChanged(int arg1);
};

#endif // MAINWINDOW_H
