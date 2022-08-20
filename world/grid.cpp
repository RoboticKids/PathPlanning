#include <math.h> 
#include "grid.h"

bool GridCreator::spinOnce()
{
    sf::Event event;

    if (_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            _window->close();
            return false;
        }

        static bool mouse_pressed = false;
        static bool mouse_released = false;

        if (event.type == sf::Event::MouseButtonPressed)
        {
            mouse_pressed = true;
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            mouse_released = true;
        }

        if (mouse_pressed && mouse_released)
        {
            mouse_pressed = mouse_released = false;
            size_t cell_id = 0;

            if (getCellId(event.mouseButton.x, event.mouseButton.y, cell_id))
            {
                std::cout << "\nCell id: " << cell_id;
                std::cout << "\nNeighbours positions:";
                std::vector<const sf::RectangleShape*> neighbours = getNeighbours(cell_id);
                for (std::size_t index = 0; index < neighbours.size(); index++)
                {
                    std::cout << " [" << neighbours.at(index)->getPosition().x
                    << ", " << neighbours.at(index)->getPosition().y << "],";
                }
            }
            else
            {
                std::cout << "Could not find cell id: " << std::endl;
            }
            std::cout << std::endl;
            
        }
    }

    _window->clear();

    for (int cell_id = 0; cell_id < _cells.size(); cell_id++)
    {
        _window->draw(_cells.at(cell_id));
    }
    
    _window->display();

    return true;
}

void GridCreator::setGrid(const uint32_t height, const uint32_t width, const uint32_t rows, const uint32_t columns, GridMode grid_mode)
{
    _height = height;
    _width = width;
    _rows = rows;
    _columns = columns;
    _cell_height = float(width) / float(_columns);
    _cell_width = float(height) / float(_rows);
    _grid_mode = grid_mode;

    _window.release();
    prepareGrid();
}

void GridCreator::prepareGrid()
{
    // TOODO: grid name into title
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(_height, _width), "Testing Grid");
    paintGrid();
}

void GridCreator::paintGrid()
{
    switch (_grid_mode)
    {
        case GridMode::CHESS_BOARD:
        {
            paintChessboard();
            break;
        }
        case GridMode::GRID_1:
        {
            paintGrid1();
            break;
        }
    }
}

void GridCreator::paintChessboard()
{
    for (std::size_t column_id = 0; column_id < _rows; column_id++)
    {
        for (std::size_t row_id = 0; row_id < _columns; row_id++)
        {
            const bool even_rows_odd_column = row_id % 2 == 0 && column_id % 2 != 0;
            const bool odd_rows_even_column = row_id % 2 != 0 && column_id % 2 == 0;

            const float x = column_id * _cell_width;
            const float y = row_id * _cell_height;

            if (even_rows_odd_column || odd_rows_even_column)
            {
                setCell(x, y, CellMode::EMPTY);
            }
            else
            {
                setCell(x, y, CellMode::OBSTACLE);
            }
            
        }
    }
}

void GridCreator::paintGrid1()
{
    for (std::size_t column_id = 0; column_id < _rows; column_id++)
    {
        for (std::size_t row_id = 0; row_id < _columns; row_id++)
        {
            const int lower_obstacle_column_multiplier = 9;
            const int upper_obstacle_column_multiplier = 12;
            const bool below_obstacle = row_id > (_rows / 4) && column_id % lower_obstacle_column_multiplier == 0;
            const bool above_obstacle = row_id < (_rows / 2) && column_id % upper_obstacle_column_multiplier == 0;
            const bool obstacle = below_obstacle || above_obstacle;

            // TODO: find better way to prevent barriers
            const bool barrier = column_id % lower_obstacle_column_multiplier == 0 && column_id % upper_obstacle_column_multiplier == 0;

            const float x = column_id * _cell_width;
            const float y = row_id * _cell_height;

            if (row_id == (_rows - 1) && column_id == 0)
            {
                setCell(x, y, CellMode::START);
            }
            else if (row_id == 0 && column_id == (_columns - 1))
            {
                setCell(x, y, CellMode::FINISH);
            }
            else if (obstacle && !barrier)
            {
                setCell(x, y, CellMode::OBSTACLE);
            }
            else
            {
                setCell(x, y, CellMode::EMPTY);
            }  
        }
    }
}

void GridCreator::setCell(const float x, const float y, const CellMode mode)
{
    sf::Vector2f cell_dimensions(_cell_width, _cell_height);
    sf::RectangleShape cell(cell_dimensions);
    setCellMode(cell, mode);
    cell.setPosition(x, y);
    _cells.push_back(cell);
}

void GridCreator::setCellMode(sf::RectangleShape& cell, const GridCreator::CellMode mode)
{
    switch (mode)
    {
        case CellMode::OBJECT:
        {
            cell.setFillColor(sf::Color::Green);
            break;
        }
        case CellMode::EMPTY:
        {
            cell.setFillColor(sf::Color::White);
            break;
        }
        case CellMode::OBSTACLE:
        {
            cell.setFillColor(sf::Color::Blue);
            break;
        }
        case CellMode::START:
        {
            cell.setFillColor(sf::Color::Red);
            break;
        }
        case CellMode::FINISH:
        {
            cell.setFillColor(sf::Color::Black);
            break;
        }
        case CellMode::UNDEFINED:
        {
            cell.setFillColor(sf::Color::Magenta);
            break;
        }
    }
}

void GridCreator::setCellMode(std::size_t id, const CellMode mode)
{
    if (id < _cells.size())
    {
        setCellMode(_cells.at(id), mode);
    }   
}

const sf::RectangleShape* GridCreator::getCell(const std::size_t id) const
{
    if (id < _cells.size())
    {
        return &_cells.at(id - getCellMinId());
    }
    else
    {
        return nullptr;
    }
}

GridCreator::CellMode GridCreator::getCellMode(const std::size_t id) const // TODO: std::map
{
    if (id < _cells.size())
    {
        if (sf::Color::Green == _cells.at(id - getCellMinId()).getFillColor())
        {
             return CellMode::OBJECT;
        }
        else if (sf::Color::Red == _cells.at(id - getCellMinId()).getFillColor())
        {
            return CellMode::START;
        }
        else if (sf::Color::Black == _cells.at(id - getCellMinId()).getFillColor())
        {
            return CellMode::FINISH;
        }
        else if (sf::Color::White == _cells.at(id - getCellMinId()).getFillColor())
        {
            return CellMode::EMPTY;
        }
        else if (sf::Color::Blue == _cells.at(id - getCellMinId()).getFillColor())
        {
            return CellMode::OBSTACLE;
        }
        else
        {
            return CellMode::UNDEFINED;
        }
    }
    else
    {
        return CellMode::UNDEFINED;
    }
}

bool GridCreator::getCellId(const float x, const float y, std::size_t& id)
{
    if (x > _width || x < 0 || y > _height || y < 0)
    {
        return false;
    }

    for (std::size_t cell_index = getCellMinId(); cell_index < _cells.size(); cell_index++)
    {
        bool fit_in_cell = _cells.at(cell_index).getGlobalBounds().contains(x, y);
        //bool fit_in_top_boundery = y == _cells.at(cell_index).getGlobalBounds().top;
        //bool fit_in_left_boundery = x == _cells.at(cell_index).getGlobalBounds().left;

        if (fit_in_cell /*|| fit_in_top_boundery || fit_in_left_boundery*/)
        {
            id = cell_index;
            return true;
        }
    }

    return false;
}

std::vector<const sf::RectangleShape*> GridCreator::getNeighbours(const std::size_t id)
{
    std::vector<const sf::RectangleShape*> cells;
    const sf::RectangleShape* required_cell = getCell(id);

    if (required_cell == nullptr)
    {
        return cells;
    }

    // Can make problems when cell will not be square
    const float diagonal_distance = sqrt(pow(_cell_width, 2.f) + pow(_cell_height, 2.f));
    const float observe_distance{diagonal_distance};

    const float right_x = required_cell->getPosition().x + diagonal_distance;
    const float right_y = required_cell->getPosition().y;

    const float left_x = required_cell->getPosition().x - diagonal_distance;
    const float left_y = required_cell->getPosition().y;

    const float upper_x = required_cell->getPosition().x;
    const float upper_y = required_cell->getPosition().y - diagonal_distance;

    const float lower_x = required_cell->getPosition().x;
    const float lower_y = required_cell->getPosition().y + diagonal_distance;

    const float right_upper_x = required_cell->getPosition().x + diagonal_distance;
    const float right_upper_y = required_cell->getPosition().y - diagonal_distance;

    const float left_upper_x = required_cell->getPosition().x - diagonal_distance;
    const float left_upper_y = required_cell->getPosition().y - diagonal_distance;

    const float right_lower_x = required_cell->getPosition().x + diagonal_distance;
    const float right_lower_y = required_cell->getPosition().y + diagonal_distance;

    const float left_lower_x = required_cell->getPosition().x - diagonal_distance;
    const float left_lower_y = required_cell->getPosition().y + diagonal_distance;

    constexpr std::size_t cell_number = 8;

    float x_position[cell_number] = {right_x, left_x, upper_x, lower_x, right_upper_x, left_upper_x, right_lower_x, left_lower_x};
    float y_position[cell_number] = {right_y, left_y, upper_y, lower_y, right_upper_y, left_upper_y, right_lower_y, left_lower_y};

    std::size_t observed_cell_id{0};
    bool cell_founded = false;

    for (std::size_t index = 0; index < cell_number; index++)
    {
        cell_founded = getCellId(x_position[index], y_position[index], observed_cell_id);

        if (cell_founded)
        {
            cells.push_back(&_cells.at(observed_cell_id));
        }
    }

    return cells;
}