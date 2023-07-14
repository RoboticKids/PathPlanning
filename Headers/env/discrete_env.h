#pragma once

#include <QMainWindow>
#include <QString>
#include <QComboBox>
#include <QGraphicsScene>
#include <QBrush>
#include "ui_mainwindow.h"

#include <iostream>
#include <vector>
#include <string>
#include "discrete_node.h"
#include <memory>
#include <cmath>
#include "../ui/env_graphics_scene.h"

class DiscreteEnvironment : public QMainWindow
{
    Q_OBJECT
    public:
        explicit DiscreteEnvironment(const int WIDTH, 
                                     const int HEIGHT, 
                                     const int ROWS, 
                                     EnvGraphicsScene* env_scene,
                                     QObject *parent = 0);

        void MakeGrid(EnvGraphicsScene* env_scene);
        void DrawGridLines(EnvGraphicsScene* env_scene);
        void UpdateNeighbours();
        void Spin();
        std::shared_ptr<DiscreteNode> GetMouseClickedNode(const int X, const int Y);
            
        // DiscreteNode *node_start;
        // DiscreteNode *node_goal;
        std::shared_ptr<DiscreteNode> node_start;
        std::shared_ptr<DiscreteNode> node_goal;


    private:
        QGraphicsScene *_env_scene;
        const int _WIDTH;
        const int _HEIGHT; 
        const int _NUM_ROWS;
        int _row_size;
        int _col_size;
        std::vector< std::vector< std::shared_ptr<DiscreteNode> > > _grid;

        QBrush _redBrush;
        QPen _blackPen;



};

