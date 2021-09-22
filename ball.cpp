#include "ball.h"

Ball::Ball(QObject *parent) : QObject(parent), QGraphicsItem()
{
    dx = 2.0f, dy = 3.0f;

    //Загрузка изображения шара
    image = QPixmap(":/images/images/ball.png");
    image = image.scaled(diameter, diameter, Qt::KeepAspectRatio);
}

Ball::~Ball() {}

QRectF Ball::boundingRect() const
{
    return QRectF(0, 0, diameter, diameter);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, image, 0, 0, diameter, diameter);

    Q_UNUSED(option); Q_UNUSED(widget);
}

void Ball::invertDx()
{
    dx = -dx;
}

void Ball::invertDy()
{
    dy = -dy;
}

void Ball::move()
{
    this->setX(this->x() + dx);
    this->setY(this->y() + dy);
}
