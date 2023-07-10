#include "env_graphics_scene.h"
#include <QDebug>

EnvGraphicsScene::EnvGraphicsScene(QObject *parent) 
    : QGraphicsScene(parent)
{
}

void
EnvGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    // qDebug() << Q_FUNC_INFO << mouseEvent->scenePos();
    emit MouseClicked(mouseEvent);
}