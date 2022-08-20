#include <iostream>

#include "grid_world.h"

int main()
{
    GridWorld world(600, 20);

    while (world.SpinOnce())
    {
        
    }

    return 0;
}
