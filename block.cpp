#include "block.h"

Block::Block(QColor color, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    pen.setColor(color);
    pen.setWidth(0);
    brush.setColor(color);
    brush.setStyle(Qt::Dense1Pattern);
}

Block::~Block() {}

QRectF Block::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen);
    painter->setBrush(brush);   //Установка кисти, которой отрисовывается объект
    painter->drawRect(0, 0, width, height);

    Q_UNUSED(option);  Q_UNUSED(widget);
}
