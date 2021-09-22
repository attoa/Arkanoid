#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

//Класс Платформа
class Platform : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Platform(int _brLeft, int _brRight, int _width, QObject *parent = nullptr);
    ~Platform();

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setWidth(int _width);

    bool isMovable;
    void setCheckX(int x);  //Установка и проверка координаты X с учетом границ

protected:
    QRectF boundingRect() const override; //Область, занимаемая платформой
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; //Рисование элемента

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    QPixmap image;          //Изображение платформы

    int width;              //Ширина платформы
    const int height = 10;  //Высота платформы
    int brLeft, brRight;    //Границы перемещения платформы

    bool captured;  //Захвачена ли платформа мышью
    int clickedX;   //Координата X нажатия мыши относительно края платформы
};

#endif // PLATFORM_H
