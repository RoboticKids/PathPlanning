#include "algorithms/breadth_first_search.h"

// BreadthFirstSearch::BreadthFirstSearch(DiscreteNode *node_start, DiscreteNode *node_goal)
//     : _node_start(node_start),
//       _node_goal(node_goal)
// {
// }



// bool
// BreadthFirstSearch::Solve()
// {
//     _set_open.push_back(_node_start);
//     _set_visited.push_back(_node_start);

//     while (_set_open.size() > 0)
//     {
//         // Get first node
//         auto node_current = _set_open.front();
//         // Pop it from the queue
//         _set_open.pop_front();

//         // Check if the current node is goal node
//         if (node_current == _node_goal)
//         {
//             std::cout << "Solution found.\n";
//             //TODO: draw a path
//             return true;
//         }
//         for (auto neighbour : node_current->neighbours)
//         {
//             if (std::find(_set_visited.begin(), _set_visited.end(), neighbour) == _set_visited.end())
//             {
//                 _set_visited.push_back(neighbour);
//                 _set_open.push_back(neighbour);
//                 std::cout << "coord:" << neighbour->GetIndexPosition()[0] << " " << neighbour->GetIndexPosition()[1] << "\n";
//                 if (neighbour != _node_start && neighbour != _node_goal)
//                 {
//                     // neighbour->MakeAlive();
//                 }
//             }
//             else
//             {
//             }
//             usleep(1000000);
//         }
//         if (node_current != _node_start)
//         {
//             node_current->MakeDead();
//         }

//     }


//     return false;
// }

bool BreadthFirstSearch(DiscreteNode *_node_start)
{
    _node_start->MakeDead();
}

// bool
// BreadthFirstSearch(DiscreteNode *_node_start, DiscreteNode *_node_goal)
// {
//     // _node_start->MakeAlive();
//     // std::deque<DiscreteNode *> _set_open;
//     // std::deque<DiscreteNode *> _set_visited;
//     // _set_open.push_back(_node_start);
//     // _set_visited.push_back(_node_start);

//     // while (_set_open.size() > 0)
//     // {
//     //     // Get first node
//     //     auto node_current = _set_open.front();
//     //     // Pop it from the queue
//     //     _set_open.pop_front();

//     //     // Check if the current node is goal node
//     //     if (node_current == _node_goal)
//     //     {
//     //         std::cout << "Solution found.\n";
//     //         //TODO: draw a path
//     //         return true;
//     //     }
//     //     for (auto neighbour : node_current->neighbours)
//     //     {
//     //         if (std::find(_set_visited.begin(), _set_visited.end(), neighbour) == _set_visited.end())
//     //         {
//     //             _set_visited.push_back(neighbour);
//     //             _set_open.push_back(neighbour);
//     //             // std::cout << "coord:" << neighbour->GetIndexPosition()[0] << " " << neighbour->GetIndexPosition()[1] << "\n";
//     //             if (neighbour != _node_start && neighbour != _node_goal)
//     //             {
//     //                 neighbour->MakeAlive();
//     //             }
//     //         }
//     //         else
//     //         {
//     //         }
//     //         // usleep(1000000);
//     //     }
//     //     if (node_current != _node_start)
//     //     {
//     //         // node_current->MakeDead();
//     //     }

//     // }


//     return false;
// }