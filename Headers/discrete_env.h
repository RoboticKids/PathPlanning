#pragma once

#include <QMainWindow>
#include <QString>
#include <QComboBox>
#include <QGraphicsScene>
#include <QBrush>

#include <iostream>
#include <vector>
#include <string>
#include "ui_mainwindow.h"

class DiscreteEnvironment : public QMainWindow
{
    Q_OBJECT
    public:
        explicit DiscreteEnvironment(const int WIDTH, 
                                     const int HEIGHT, 
                                     const int ROWS, 
                                     QObject *parent = 0);

        void MakeGrid(QGraphicsScene* env_scene);
        void DrawGridLines(QGraphicsScene* env_scene);
        void Spin();

    private:
        QGraphicsScene *_env_scene;
        const int _WIDTH;
        const int _HEIGHT; 
        const int _NUM_ROWS;

        int _row_size;
        int _col_size;

        QBrush _redBrush;
        QPen _blackPen;



};

