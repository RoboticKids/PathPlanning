#pragma once
#include "algorithms/solver_template.h"


class BreadthFirstSearch : public Solver
{
    public:
        BreadthFirstSearch(DiscreteNode *node_start, DiscreteNode *node_goal);

        bool Solve() override;

    private:
        DiscreteNode *_node_start;
        DiscreteNode *_node_goal;
        std::deque<DiscreteNode *> _set_open;
        std::deque<DiscreteNode *> _set_visited;
};



// bool BreadthFirstSearch(DiscreteNode *_node_start);
// bool BreadthFirstSearch(DiscreteNode *_node_start, DiscreteNode *_node_goal);