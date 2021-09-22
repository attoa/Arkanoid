#ifndef SCENE_H
#define SCENE_H

#include <QKeyEvent>
#include <QGraphicsScene>

#include "platform.h"

class Scene : public QGraphicsScene
{
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();

protected:
    Platform *platform = nullptr;

    void keyPressEvent(QKeyEvent *event) override;
};

#endif // SCENE_H
