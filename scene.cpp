#include "scene.h"

#define SHIFT 45    //Величина сдвига платформы

Scene::Scene(QObject *parent) : QGraphicsScene(parent) {}

Scene::~Scene() {}

void Scene::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);

    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
    {
        //Поиск объекта платформы
        if (platform == nullptr)
        {
            for (auto item : this->items())
            {
                if ((platform = dynamic_cast<Platform*>(item)))
                    break;
            }
        }

        //Перемещение платформы
        if (platform != nullptr)
        {
            switch (event->key()) {
            case Qt::Key_Left:
                platform->setCheckX(platform->x() - SHIFT);
                break;
            case Qt::Key_Right:
                platform->setCheckX(platform->x() + SHIFT);
                break;
            }
        }
    }
}
