#include "env/discrete_env.h"

DiscreteEnvironment::DiscreteEnvironment(const int WIDTH, 
                                         const int HEIGHT, 
                                         const int ROWS, 
                                         EnvGraphicsScene* env_scene,
                                         QObject *parent)
    : _WIDTH(WIDTH)
    , _HEIGHT(HEIGHT)
    , _NUM_ROWS(ROWS)
    , _redBrush(Qt::red)
    , _blackPen(Qt::black)
{
    _row_size = static_cast<int>(_HEIGHT / _NUM_ROWS);
    _col_size = static_cast<int>(_WIDTH / _NUM_ROWS);

    for (int row=0; row<_NUM_ROWS; ++row)
    {
        std::vector<std::shared_ptr<DiscreteNode>> row_nodes;
        for (int col=0; col<_NUM_ROWS; ++col)
        {
            auto temp_node = std::make_shared<DiscreteNode>(row, col, std::vector<int>{_row_size,_col_size}, _NUM_ROWS, env_scene); 
            row_nodes.push_back(temp_node);
        }
        _grid.push_back(row_nodes);
    }

    
}

void
DiscreteEnvironment::MakeGrid(EnvGraphicsScene* env_scene)
{
    DrawGridLines(env_scene);
}

void
DiscreteEnvironment::DrawGridLines(EnvGraphicsScene* env_scene)
{
    for (uint i=0; i<_NUM_ROWS+2; ++i)
    {
        env_scene->addLine(0, i*_row_size, _WIDTH, i*_row_size);    // draw horizontal line
        env_scene->addLine(i*_col_size, 0, i*_col_size, _HEIGHT);    // draw vertical line
    }
}


std::shared_ptr<DiscreteNode>
DiscreteEnvironment::GetMouseClickedNode(const int X, const int Y)
{
    const int ROW = std::floor(Y / _row_size);
    const int COL = std::floor(X / _col_size);
    return _grid[ROW][COL];
}

void 
DiscreteEnvironment::UpdateNeighbours()
{
     for (int row=0; row<_NUM_ROWS; ++row)
    {
        for (int col=0; col<_NUM_ROWS; ++col)
        {
            auto node = _grid[row][col];
            node->UpdateNeighbours(_grid);
        }
    }
}


void
DiscreteEnvironment::Spin()
{

}

