#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

//Класс Блок
class Block : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Block(QColor color, QObject *parent = nullptr);
    ~Block();

    static int getWidth() { return width; }
    static int getHeight() { return height; }

protected:
    QRectF boundingRect() const override; //Область, занимаемая блоком
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; //Рисование элемента

private:
    static const int width = 30, height = 20;  //Размеры блока

    QBrush brush; QPen pen; //Инструменты рисования
};

#endif // BLOCK_H
