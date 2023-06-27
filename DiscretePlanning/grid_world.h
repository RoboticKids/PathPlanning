#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "forward_search.h"


enum class SearchAlgorithm
{
    FORWARD_SEARCH,
    BREADTH_FIRST_SEARCH,
    DEPTH_FIRST_SEARCH
};

enum class NodeMode
{
    EMPTY,
    START,
    GOAL,
    OBSTACLE
};

struct Node
{
    int index_row;
    int index_col;
    NodeMode mode;
    Node *upper_neighbour;
    Node *bottom_neighbour;
    Node *left_neighbour;
    Node *right_neighbour;
    Node(int row, int col) : index_row(row), index_col(col), mode(NodeMode::EMPTY), upper_neighbour(nullptr),
                             bottom_neighbour(nullptr), left_neighbour(nullptr), right_neighbour(nullptr) {}
    Node(int row, int col, Node *upper, Node *bottom, Node *left, Node *right) : index_row(row), index_col(col), mode(NodeMode::EMPTY), 
                                                                                 upper_neighbour(upper), bottom_neighbour(bottom), 
                                                                                 left_neighbour(left), right_neighbour(right) {}
    std::array<int, 2> GetPosition()
    {
        return std::array<int, 2>{index_row, index_col};
    }
};


class GridWorld
{
    public:
        GridWorld(const int width, const int rows, const SearchAlgorithm algo);
        ~GridWorld();

        bool SpinOnce();

        void DrawGrid();
        Node *GetMouseClickedNode(const int x, const int y);
    
    
        void MakeStartNode(Node *node);
        void MakeGoalNode(Node *node);
        void MakeObstacleNode(Node *node);
        void ClearNode(Node *node);

        bool IsNodeStart(Node *node);
        bool IsNodeGoal(Node *node);
        bool IsNodeObstacle(Node *node);


        Node *start_node;
        Node *goal_node;
    
    private:
        sf::RenderWindow _window;

        const int _width;
        const int _rows;
        int _grid_size;
        std::vector<std::vector<Node>> _grid;

        SearchAlgorithm _algorithm;
};

