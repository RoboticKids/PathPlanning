#pragma once

#include <QMainWindow>
#include <QString>
#include <QComboBox>
#include <QGraphicsScene>
#include <QBrush>
#include "ui_mainwindow.h"


class ContinuousEnvironment : public QMainWindow
{
    Q_OBJECT
    public:
        explicit ContinuousEnvironment(const int WIDTH, 
                                       const int HEIGHT, 
                                       QObject *parent = 0);
        void ResetEnv(QGraphicsScene *scene);

    private:

};