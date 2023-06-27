#include <iostream>

#include "grid_world.h"

int main()
{
    GridWorld world(600, 20, SearchAlgorithm::BREADTH_FIRST_SEARCH);

    while (world.SpinOnce())
    {
        
    }

    return 0;
}
