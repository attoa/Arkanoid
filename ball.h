#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

//Класс Шар
class Ball : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Ball(QObject *parent = nullptr);
    ~Ball();

    int getDiameter() const { return diameter; }

    float dx, dy;       //Составляющие угла полета шара

    void invertDx();    //Отразить угол по оси X
    void invertDy();    //Отразить угол по оси Y

    void move();        //Переместить шар

protected:
    QRectF boundingRect() const override; //Область, занимаемая шаром
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; //Рисование элемента

private:
    QPixmap image;              //Изображение шара

    const int diameter = 20;    //Диаметр шара
};

#endif // BALL_H
