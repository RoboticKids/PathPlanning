#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "env/discrete_node.h"
#include <deque>
#include <unistd.h>


class Solver
{
    public:
        Solver(/* args */)
        {

        }

        virtual bool Solve()
        {
            std::cerr << "Not implemented!\n";    
            return false;
        }

    private:
        /* data */

};


