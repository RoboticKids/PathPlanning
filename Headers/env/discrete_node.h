#pragma once
#include <vector>
#include <QColor>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <iostream>
#include <memory>

class DiscreteNode
{
    public:
        DiscreteNode(const int INDEX_ROW, 
                     const int INDEX_COL, 
                     const std::vector<int> &grid_size,
                     const int NUM_ROWS,
                     QGraphicsScene *scene);


        std::vector<int> GetIndexPosition();
        // Check if a node has been visited and is dead
        bool isDead();
        // Check if a node has been visited
        bool isAlive();
        // Check if a node is an obstacle
        bool isObstacle();
        // Reset a node to the initial state
        void Reset();
        // Make a node dead
        void MakeDead();
        // Make a node alive
        void MakeAlive();
        // Convert a node into an obstacle
        void MakeObstacle();
        // Convert a node into a start node
        void MakeStart();
        // Convert a node into a goal node
        void MakeGoal();
        // Make path node
        void MakePath();
        // Update neighbours
        void UpdateNeighbours(std::vector< std::vector< std::shared_ptr<DiscreteNode> > > &grid);

        std::vector<DiscreteNode *> neighbours; 

    private:
        int _index_row;
        int _index_col;
        int _position_x;
        int _position_y;
        int _num_rows;
        std::vector<int> _grid_size;
        // QColor _color;
        Qt::GlobalColor _color;

        QGraphicsRectItem* _node_visual;


};

// class NodeColors
// {
//     public:
//         NodeColors(){}
//         QColor red(Qt::GlobalColor::red);

// };