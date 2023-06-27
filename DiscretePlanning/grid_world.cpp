#include "grid_world.h"

GridWorld::GridWorld(const int width, const int rows, const SearchAlgorithm algo)
    : _width(width)
     ,_rows(rows)
     ,_window(sf::VideoMode(width, width), "Discrete World")
     ,_algorithm(algo)
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
                    if (!IsNodeStart(node) && !IsNodeGoal(node)) ClearNode(node);
                }
                // TODO: Reset environment
                else
                {
                }
            }
            // Start algorithm with "space" keyboard
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                switch (_algorithm)
                {
                    case SearchAlgorithm::FORWARD_SEARCH:
                    {
                        std::cout << "space\n";
                        discrete_algorithms::ForwardSearch();
                        break;
                    }
                    default:
                        break;
                }
            }

        }

        // Draw
        _window.clear();
        DrawGrid();
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
void GridWorld::DrawGrid()
{
    // White background
    sf::RectangleShape background(sf::Vector2f(_width, _width));
    background.setFillColor(sf::Color(255,255,255));
    background.setPosition(sf::Vector2f(0, 0));
    _window.draw(background);

    // Nodes visualization
    for (int row=0; row<_rows; ++row)
    {
        for (int col=0; col<_rows; ++col)
        {
            switch (_grid[row][col].mode)
            {
                case NodeMode::START:
                {
                    sf::RectangleShape node_rect(sf::Vector2f(_grid_size, _grid_size));
                    node_rect.setFillColor(sf::Color(139,69,19));
                    node_rect.setPosition(sf::Vector2f(col*_grid_size, row*_grid_size));
                    _window.draw(node_rect);
                    break;
                }
                case NodeMode::GOAL:
                {
                    sf::RectangleShape node_rect(sf::Vector2f(_grid_size, _grid_size));
                    node_rect.setFillColor(sf::Color(0,255,0));
                    node_rect.setPosition(sf::Vector2f(col*_grid_size, row*_grid_size));
                    _window.draw(node_rect);
                    break;
                }
                case NodeMode::OBSTACLE:
                {
                    sf::RectangleShape node_rect(sf::Vector2f(_grid_size, _grid_size));
                    node_rect.setFillColor(sf::Color(0,0,0));
                    node_rect.setPosition(sf::Vector2f(col*_grid_size, row*_grid_size));
                    _window.draw(node_rect);
                    break;
                }
                default:
                {
                    sf::RectangleShape node_rect(sf::Vector2f(_grid_size, _grid_size));
                    node_rect.setFillColor(sf::Color(255,255,255));
                    node_rect.setPosition(sf::Vector2f(col*_grid_size, row*_grid_size));
                    _window.draw(node_rect);
                    break;
                }
            }
        }
    }

    // Gray grid lines
    for (int row=0; row<_rows; ++row)
    {
        sf::Vertex row_line[] = {sf::Vertex(sf::Vector2f(0, row*_grid_size), sf::Color(128,128,128)), sf::Vertex(sf::Vector2f(_width, row*_grid_size), sf::Color(128,128,128))};
        _window.draw(row_line, 2, sf::Lines);
        for (int col=0; col<_rows; ++col)
        {
            sf::Vertex col_line[] = {sf::Vertex(sf::Vector2f(row*_grid_size, 0), sf::Color(128,128,128)), sf::Vertex(sf::Vector2f(row*_grid_size, _width), sf::Color(128,128,128))};
            _window.draw(col_line, 2, sf::Lines);
        }
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