#include <iostream>
#include <SFML/Graphics.hpp>
#include "grid.h"

int main()
{
    /* Test */
    // GridCreator grid;
    // grid.setGrid(500,500,40,40, GridCreator::GridMode::GRID_1);

    // size_t cell_counter = 0;
    // GridCreator::CellMode previous_mode{GridCreator::CellMode::UNDEFINED};

    // while (grid.spinOnce())
    // {
    //     if (cell_counter < grid.getCellsQuantity())
    //     {
    //         if (cell_counter != 0)
    //         {
    //             grid.setCellMode((cell_counter - 1), previous_mode);
    //         }

    //         previous_mode = grid.getCellMode(cell_counter);
    //         grid.setCellMode(cell_counter, GridCreator::CellMode::OBJECT);
    //         cell_counter++;
    //     }
    // }

    return 0;
}