#pragma once
#include "algorithms/solver_template.h"


class DepthFirstSearch : public Solver
{
    public:
        DepthFirstSearch(DiscreteNode *node_start, DiscreteNode *node_goal);

        void run() override;
        void VisualizePath() override;

    private:
        DiscreteNode *_node_start;
        DiscreteNode *_node_goal;
        std::deque<DiscreteNode *> _set_open;
        std::deque<DiscreteNode *> _set_visited;
        std::unordered_map<DiscreteNode *, DiscreteNode *> _set_camefrom;
    
};

