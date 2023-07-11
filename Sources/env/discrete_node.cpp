#include "env/discrete_node.h"

DiscreteNode::DiscreteNode(const int INDEX_ROW, 
                           const int INDEX_COL, 
                           const std::vector<int> &grid_size,
                           const int NUM_ROWS,
                           QGraphicsScene *scene)
{
    _index_row = INDEX_ROW;
    _index_col = INDEX_COL;
    _grid_size = grid_size; // [row_size, col_size]
    _num_rows = NUM_ROWS;
    _position_x = _index_col*grid_size[1];
    _position_y = _index_row*grid_size[0];

    _node_visual = new QGraphicsRectItem(_position_x, _position_y, _grid_size[1], _grid_size[0]);
    scene->addItem(_node_visual);
}


std::vector<int> 
DiscreteNode::GetIndexPosition()
{
    return std::vector<int>{_index_row, _index_col};
}

bool
DiscreteNode::isDead()
{
    return _color == Qt::darkGray;
}

bool 
DiscreteNode::isAlive()
{
    return _color == Qt::green;
}

bool 
DiscreteNode::isObstacle()
{
    return _color == Qt::black;
}

void
DiscreteNode::Reset()
{
    _color == Qt::white;
    _node_visual->setBrush(QBrush(_color, Qt::SolidPattern));
    _node_visual->update();
}

void 
DiscreteNode::MakeDead()
{
    _color == Qt::darkGray;
    _node_visual->setBrush(QBrush(_color, Qt::SolidPattern));
    _node_visual->update();
}

void 
DiscreteNode::MakeAlive()
{
    _color == Qt::darkYellow;
    _node_visual->setBrush(QBrush(_color, Qt::SolidPattern));
    _node_visual->update();
}

void 
DiscreteNode::MakeObstacle()
{
    _color = Qt::black;
    _node_visual->setBrush(QBrush(_color, Qt::SolidPattern));
    _node_visual->update();
}

void 
DiscreteNode::MakeStart()
{
    _color = Qt::darkRed;
    _node_visual->setBrush(QBrush(_color, Qt::SolidPattern));
    _node_visual->update();
}

void 
DiscreteNode::MakeGoal()
{
    _color = Qt::red;
    _node_visual->setBrush(QBrush(_color, Qt::SolidPattern));
    _node_visual->update();
}

void
DiscreteNode::MakePath()
{
    _color = Qt::green;
    _node_visual->setBrush(QBrush(_color, Qt::SolidPattern));
    _node_visual->update();
}


void 
DiscreteNode::UpdateNeighbours(std::vector< std::vector< std::shared_ptr<DiscreteNode> > > &grid)
{
    _neighbours.clear();
    //TODO: fix NUM_ROWS
    //TODO: add options to UI for diag movement
    // Neighbour on the right
    if (_index_col < (_num_rows-1) && !grid[_index_row][_index_col+1]->isObstacle())
    {
        _neighbours.push_back(grid[_index_row][_index_col+1].get());
    } 
    // Neighbour on the left
    if (_index_col > 0 && !grid[_index_row][_index_col-1]->isObstacle()) 
    {
        _neighbours.push_back(grid[_index_row][_index_col-1].get());
    }
    // Upper neighbour
    if (_index_row > 0 && !grid[_index_row-1][_index_col]->isObstacle()) 
    {
        _neighbours.push_back(grid[_index_row-1][_index_col].get());
    }
    // Bottom neighbour
    if (_index_row < (_num_rows-1) && !grid[_index_row+1][_index_col]->isObstacle()) 
    {
        _neighbours.push_back(grid[_index_row+1][_index_col].get());
    }
}
