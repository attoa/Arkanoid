#include "platform.h"

Platform::Platform(int _brLeft, int _brRight, int _width, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    //Установка границ перемещения платформы
    brLeft = _brLeft; brRight = _brRight;

    //Установка ширины платформы
    width = _width;

    //Загрузка изображения платформы
    image = QPixmap(":/images/images/platform.png");
    image = image.scaled(width, height, Qt::IgnoreAspectRatio);

    isMovable = false;
    captured = false;

    //Разрешение событий наведения мыши
    this->setAcceptHoverEvents(true);
}

Platform::~Platform() {}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, image, 0, 0, width, height);

    Q_UNUSED(option); Q_UNUSED(widget);
}

QRectF Platform::boundingRect() const
{
    return QRectF(0, 0, width, height);
}

void Platform::setWidth(int _width)
{
    width = _width;
    image = image.scaled(width, height, Qt::IgnoreAspectRatio);
}

void Platform::setCheckX(int x)
{
    if (isMovable)
    {
        this->setX(x);

        if (this->x() < brLeft)
            this->setX(brLeft);

        else if (this->x() > brRight - width)
            this->setX(brRight - width);
    }
}

void Platform::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isMovable && event->button() == Qt::LeftButton)
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor)); //Курсор сжатой руки
        captured = true;
        clickedX = event->pos().x();
    }
}

void Platform::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (captured)
        //Установка переведенной координаты X из локальной системы элемента в координаты сцены
        setCheckX(mapToScene(event->pos()).x() - clickedX);
}

void Platform::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (captured)
    {
        captured = false;
        this->setCursor(QCursor(Qt::ArrowCursor));      //Восстановление курсора
    }

    Q_UNUSED(event);
}

void Platform::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (isMovable)
        this->setCursor(QCursor(Qt::OpenHandCursor));   //Курсор руки

    Q_UNUSED(event);
}

void Platform::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (isMovable)
        this->setCursor(QCursor(Qt::ArrowCursor));      //Восстановление курсора

    Q_UNUSED(event);
}
