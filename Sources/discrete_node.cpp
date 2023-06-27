#include "discrete_node.h"

DiscreteNode::DiscreteNode(const int INDEX_ROW, 
                           const int INDEX_COL, 
                           const std::vector<int> &grid_size)
{
    _index_row = INDEX_ROW;
    _index_col = INDEX_COL;
    _grid_size = grid_size; // [row_size, col_size]

    _position_x = _index_col*grid_size[1];
    _position_y = _index_row*grid_size[0];

    _node_visual = new QGraphicsRectItem(_position_x, _position_y, _grid_size[1], _grid_size[0]);
}


std::vector<int> 
DiscreteNode::GetIndexPosition()
{
    return std::vector<int>{_index_row, _index_col};
}

bool
DiscreteNode::isDead()
{
    return false;
}

bool 
DiscreteNode::isAlive()
{
    return false;
}

bool 
DiscreteNode::isObstacle()
{
    return false;
}

void
DiscreteNode::Reset()
{

}

void 
DiscreteNode::MakeDead()
{

}

void 
DiscreteNode::MakeAlive()
{

}

void 
DiscreteNode::MakeObstacle()
{
    _color = Qt::black;
}

void 
DiscreteNode::MakeStart()
{
    // _color.setRgb(Qt::yellow);
    _color = Qt::yellow;
}

void 
DiscreteNode::MakeGoal()
{
    _color = Qt::green;
}

void 
DiscreteNode::Draw(QGraphicsScene *scene)
{
    _node_visual->setBrush(QBrush(_color, Qt::SolidPattern));
    scene->addItem(_node_visual);
}