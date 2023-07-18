#include "algorithms/depth_first_search.h"

DepthFirstSearch::DepthFirstSearch(DiscreteNode *node_start, DiscreteNode *node_goal)
    : _node_start(node_start),
      _node_goal(node_goal)
{
}



void
DepthFirstSearch::run()
{
    _set_open.push_back(_node_start);
    _set_visited.push_back(_node_start);

    while (_set_open.size() > 0)
    {
        // Get first node
        auto node_current = _set_open.back();
        // Pop it from the queue
        _set_open.pop_back();

        // Check if the current node is goal node
        if (node_current == _node_goal)
        {
            VisualizePath();
            emit SolverFinished();
            return ;
        }
        for (auto neighbour : node_current->neighbours)
        {
            if (std::find(_set_visited.begin(), _set_visited.end(), neighbour) == _set_visited.end())
            {
                _set_visited.push_back(neighbour);
                _set_open.push_back(neighbour);
                _set_camefrom[neighbour] = node_current;
                if (neighbour != _node_start && neighbour != _node_goal)
                {
                    neighbour->MakeAlive();
                }
            }
            else
            {
            }
            usleep(20000);
        }
        if (node_current != _node_start)
        {
            node_current->MakeDead();
        }

    }
    std::cout << "No solution found\n";
    emit SolverFinished();
}

void
DepthFirstSearch::VisualizePath()
{
    auto node_current = _node_goal;
    while (_set_camefrom.find(node_current) != _set_camefrom.end())
    {
        usleep(20000);
        node_current = _set_camefrom[node_current];
        node_current->MakePath();
    }
    node_current->MakeStart();
}