#pragma once 

#include <iostream>
#include <SFML/Graphics.hpp>

// TODO: set formatter

class GridCreator
{
    public:

        enum class GridMode
        {
            CHESS_BOARD,
            GRID_1,
        };

        enum class CellMode
        {
            OBJECT,
            EMPTY,
            OBSTACLE,
            START,
            FINISH,
            UNDEFINED,
        };

        GridCreator(){}
        ~GridCreator() = default;

        bool spinOnce();
        
        void setGrid(const uint32_t height, const uint32_t width, const uint32_t rows, const uint32_t columns, GridMode grid_mode = GridMode::GRID_1);
        void setCellMode(std::size_t id, const CellMode mode);
        
        [[nodiscard]] const sf::RectangleShape* getCell(const std::size_t id) const;
        [[nodiscard]] std::size_t getCellId(const float x, const float y) const;
        [[nodiscard]] CellMode getCellMode(const std::size_t id) const;
        [[nodiscard]] std::size_t getCellsQuantity() const {return _cells.size();}
        [[nodiscard]] std::size_t getCellMinId() const {return 0;};

        std::unique_ptr<sf::RenderWindow> _window;
        
    private:

        uint32_t _height{0};
        uint32_t _width{0};
        uint32_t _rows{0};
        uint32_t _columns{0};
        float _cell_height{0};
        float _cell_width {0};
        GridMode _grid_mode{GridMode::GRID_1};
        
        std::vector<sf::RectangleShape> _cells;

        void prepareGrid();
        void paintGrid();
        void paintChessboard();
        void paintGrid1();
        void setCell(const float x, const float y, const CellMode mode);
        void setCellMode(sf::RectangleShape& cell, const CellMode mode);
};