#include "grid_world.h"

GridWorld::GridWorld(const int width, const int rows)
    : _width(width)
     ,_rows(rows)
     ,_window(sf::VideoMode(width, width), "Discrete World")
{
    _grid_size = _width / rows;     // int division

    // Create grid
    for (int row=0; row<_rows; row++)
    {
        std::vector<Node> temp;
        for (int col=0; col<_rows; col++)
        {
            temp.push_back(Node(row, col));
        }
        _grid.push_back(temp);
    }
}

GridWorld::~GridWorld()
{
}

///////////////////////////////////////////////////////////////////////
/// @brief
/// @param
///////////////////////////////////////////////////////////////////////
bool GridWorld::SpinOnce()
{
    if (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
            
            // Check mouse click
            if (event.type == sf::Event::MouseButtonReleased)
            {
                // Left click for setting start/goal/obstacle
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    auto node = GetMouseClickedNode(event.mouseButton.x, event.mouseButton.y);
                    if (start_node == nullptr)
                    {
                        MakeStartNode(node);
                    }
                    else if (goal_node == nullptr && !IsNodeStart(node))
                    {
                        MakeGoalNode(node);
                    }
                    else if (!IsNodeStart(node) && !IsNodeGoal(node))
                    {
                        MakeObstacleNode(node);
                    }
                    else
                    {}
                }
                // Remove obstacle with right click
                else if (event.mouseButton.button == sf::Mouse::Button::Right)
                {
                    auto node = GetMouseClickedNode(event.mouseButton.x, event.mouseButton.y);
                    ClearNode(node);
                }
                else
                {
                }
            }
            // Start algorithm with "space" keyboard
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                std::cout << "Space\n";
                // TODO: Start an algorithm
            }

        }
        // Update

        // Draw
        _window.clear();

        _window.display();

        return true;
    }
    else
    {
        return false;
    }
}

///////////////////////////////////////////////////////////////////////
/// @brief
/// @param
///////////////////////////////////////////////////////////////////////
Node *GridWorld::GetMouseClickedNode(const int x, const int y)
{
    int row = y / _grid_size;
    int col = x / _grid_size;
    return &_grid[row][col];
}

///////////////////////////////////////////////////////////////////////
/// @brief
/// @param
///////////////////////////////////////////////////////////////////////
void GridWorld::MakeStartNode(Node *node)
{
    node->mode = NodeMode::START;
    start_node = node;
}

///////////////////////////////////////////////////////////////////////
/// @brief
/// @param
///////////////////////////////////////////////////////////////////////
void GridWorld::MakeGoalNode(Node *node)
{
    node->mode = NodeMode::GOAL;
    goal_node = node;
}

///////////////////////////////////////////////////////////////////////
/// @brief
/// @param
///////////////////////////////////////////////////////////////////////
void GridWorld::MakeObstacleNode(Node *node)
{
    node->mode = NodeMode::OBSTACLE;
}

///////////////////////////////////////////////////////////////////////
/// @brief
/// @param
///////////////////////////////////////////////////////////////////////
void GridWorld::ClearNode(Node *node)
{
    node->mode = NodeMode::EMPTY;
}

///////////////////////////////////////////////////////////////////////
/// @brief
/// @param
///////////////////////////////////////////////////////////////////////
bool GridWorld::IsNodeStart(Node *node)
{
    return node->mode == NodeMode::START;
}

///////////////////////////////////////////////////////////////////////
/// @brief
/// @param
///////////////////////////////////////////////////////////////////////
bool GridWorld::IsNodeGoal(Node *node)
{
    return node->mode == NodeMode::GOAL;
}

///////////////////////////////////////////////////////////////////////
/// @brief
/// @param
///////////////////////////////////////////////////////////////////////
bool GridWorld::IsNodeObstacle(Node *node)
{
    return node->mode == NodeMode::OBSTACLE;
}