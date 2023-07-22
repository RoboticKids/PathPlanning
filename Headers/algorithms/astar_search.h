#pragma once

#include "algorithms/solver_template.h"


class AstarSearch : public Solver
{
    public:
        AstarSearch(DiscreteNode *node_start, DiscreteNode *node_goal);

        void run() override;
        void VisualizePath() override;

        float optimal_cost_to_come{0.0};

    private:
        DiscreteNode *_node_start;
        DiscreteNode *_node_goal;
        // std::deque<DiscreteNode *> _set_open;
        std::deque<DiscreteNode *> _set_visited;
        std::unordered_map<DiscreteNode *, DiscreteNode *> _set_camefrom;
        std::unordered_map<DiscreteNode *, float> _set_open;

        float CostToGoal(const std::vector<int> &p1, const std::vector<int> &p2);
        // struct CompareCostValues;
};