#include "algorithms/astar_search.h"

AstarSearch::AstarSearch(DiscreteNode *node_start, DiscreteNode *node_goal)
    : _node_start(node_start),
      _node_goal(node_goal)
{
}



void
AstarSearch::run()
{
   // _set_open.push_back(_node_start);
    _set_visited.push_back(_node_start);
    _node_start->cost = 0.0;
    _set_open[_node_start] = _node_start->cost + CostToGoal(_node_start->GetIndexPosition(), _node_goal->GetIndexPosition());
    

    while (_set_open.size() > 0)
    {
        // Q.GetFirst() (get state with the lowest cost-to-go)
        // and remove it from the hashmap
        // return std::pair<Node, float cost>
        auto current_node_pair = *std::min_element(_set_open.begin(), _set_open.end(),
                                                [&](const auto& l, const auto& r) {
                                                    auto G_l = CostToGoal(l.first->GetIndexPosition(), _node_goal->GetIndexPosition());
                                                    auto G_r = CostToGoal(r.first->GetIndexPosition(), _node_goal->GetIndexPosition());
                                                    return (l.second+G_l) < (r.second+G_r);
                                                    });
        _set_open.erase(current_node_pair.first);

        // Current state will become dead state so its cost_to_come can become optimal
        optimal_cost_to_come = current_node_pair.second;
        auto node_current = current_node_pair.first;

        // Check if the current node is goal node
        if (node_current == _node_goal)
        {
            std::cout << "Optimal cost: " << optimal_cost_to_come << "\n";
            VisualizePath();
            emit SolverFinished();
            return ;
        }


        for (auto neighbour : node_current->neighbours)
        {
            if (!neighbour->isDead())
            {
                float cost_to_come = optimal_cost_to_come + neighbour->cost;

                // If node wasn't visited
                if (std::find(_set_visited.begin(), _set_visited.end(), neighbour) == _set_visited.end())
                {
                    neighbour->cost = cost_to_come;

                    // add/change neighbor.cost into Q function
                    _set_visited.push_back(neighbour);
                    _set_open[neighbour] = neighbour->cost;

                    // Visualize final path
                    _set_camefrom[neighbour] = node_current;
                    if (neighbour != _node_start && neighbour != _node_goal)
                    {
                        neighbour->MakeAlive();
                    }
                }
                else
                {
                    if (cost_to_come < neighbour->cost)
                    {
                        _set_open[neighbour] = cost_to_come;
                        _set_camefrom[neighbour] = node_current;
                    }
                }
            usleep(20000);
            }

            
        }
        if (node_current != _node_start)
        {
            node_current->MakeDead();
        }

    }
    std::cout << "No solution found\n";
    emit SolverFinished();
}


// struct AstarSearch::CompareCostValues
// {
//     bool operator()(const std::pair<DiscreteNode *, float> &l, const std::pair<DiscreteNode *, float> &r) const
//     {   
//         auto l_pos = l.first->GetIndexPosition();
//         auto goal_pos = _node_goal->GetIndexPosition();

//         auto G_l = CostToGoal(l.first->GetIndexPosition(), _node_goal->GetIndexPosition());
//         return l.second < r.second;
//     }

// };

float AstarSearch::CostToGoal(const std::vector<int> &p1, const std::vector<int> &p2)
{
    //L2 norm
    return std::sqrt(std::pow(p1[0]-p2[0], 2) + std::pow(p1[1]-p2[1], 2));
}


void
AstarSearch::VisualizePath()
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