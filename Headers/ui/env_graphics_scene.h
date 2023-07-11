#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class EnvGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
    public:
        explicit EnvGraphicsScene(QObject *parent = 0);
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    
    signals:
        void MouseClicked(QGraphicsSceneMouseEvent * mouseEvent);

    public slots:

    private:
};


