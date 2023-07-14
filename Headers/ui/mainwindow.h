#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QComboBox>
#include <QGraphicsScene>
#include <QBrush>

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>

#include "env_graphics_scene.h"
#include "../env/discrete_env.h"
#include "../env/continuous_env.h"

#include "../algorithms/breadth_first_search.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        // Env dimensions
        const int _WIDTH{960};
        const int _HEIGHT{800};
        const int _ROWS{10};


        // Planners
        const std::vector<QString> _environment_list{"Discrete", "Continuous"};
        const std::vector<QString> _planners_discrete{"Depth-First Search", "Breadth-First Search"};
        const std::vector<QString> _planners_continuous{"Probabilistic Roadmaps"};
        std::shared_ptr<DiscreteEnvironment> _env_discrete;
        std::shared_ptr<ContinuousEnvironment> _env_continuous;
        std::shared_ptr<BreadthFirstSearch> _solver;

        // Drawing
        // QGraphicsScene* _env_scene;
        std::shared_ptr<EnvGraphicsScene> _env_scene;

    private slots:
        void on_MouseClicked(QGraphicsSceneMouseEvent * mouseEvent);
        void on_ButtonSolveClicked();
        void on_ButtonResetClicked();
        void on_EnvironmentChanged(int env_idx);
        void on_PlannerChanged(int planner_idx);
        void on_SolverFinished();
};

#endif // MAINWINDOW_H
