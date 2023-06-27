#include "discrete_env.h"

DiscreteEnvironment::DiscreteEnvironment(const int WIDTH, 
                                         const int HEIGHT, 
                                         const int ROWS, 
                                         QObject *parent)
    : _WIDTH(WIDTH)
    , _HEIGHT(HEIGHT)
    , _NUM_ROWS(ROWS)
    , _redBrush(Qt::red)
    , _blackPen(Qt::black)
{
    _row_size = static_cast<int>(_HEIGHT / _NUM_ROWS);
    _col_size = static_cast<int>(_WIDTH / _NUM_ROWS);

    
}

void
DiscreteEnvironment::MakeGrid(QGraphicsScene* env_scene)
{
    DrawGridLines(env_scene);
    DiscreteNode node(0, 0, std::vector<int>{_row_size,_col_size});
    node.MakeStart();
    node.Draw(env_scene);
}

void
DiscreteEnvironment::DrawGridLines(QGraphicsScene* env_scene)
{
    for (uint i=0; i<_NUM_ROWS+2; ++i)
    {
        env_scene->addLine(0, i*_row_size, _WIDTH, i*_row_size);    // draw horizontal line
        env_scene->addLine(i*_col_size, 0, i*_col_size, _HEIGHT);    // draw vertical line
    }
}

void
DiscreteEnvironment::Spin()
{

}

