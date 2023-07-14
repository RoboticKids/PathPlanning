#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "env/discrete_node.h"
#include <deque>
#include <unistd.h>
#include <unordered_map>
#include <QThread>

class Solver : public QThread
{
    Q_OBJECT
    public:
        explicit Solver(QObject *parent = 0) : QThread(parent)
        {

        }


        virtual void run()
        {
            std::cerr << "Solver is not implemented!\n";    
        }
        
        virtual void VisualizePath()
        {
            std::cerr << "Visualizing path is not implemented!\n";    
        }


    private:
        /* data */
    
    signals:
        void SolverFinished();

};


