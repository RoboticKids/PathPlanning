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
#include "discrete_env.h"
#include "continuous_env.h"

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
        DiscreteEnvironment *_env_discrete;
        ContinuousEnvironment *_env_continuous;

        // Drawing
        QGraphicsScene* _env_scene;

    private slots:
        void on_ButtonSolveClicked();
        void on_ButtonResetClicked();
        void on_EnvironmentChanged(int env_idx);
        void on_PlannerChanged(int planner_idx);
        void on_MouseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MAINWINDOW_H
