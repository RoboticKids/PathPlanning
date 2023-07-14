#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Buttons
    connect(ui->button_SolveEnv, &QPushButton::clicked, this, &MainWindow::on_ButtonSolveClicked);
    connect(ui->button_ResetEnv, &QPushButton::clicked, this, &MainWindow::on_ButtonResetClicked);

    // Init combo-boxes
    connect(ui->comboBox_env_type, SIGNAL(activated(int)), this, SLOT(on_EnvironmentChanged(int)));
    connect(ui->comboBox_planner_type, SIGNAL(activated(int)), this, SLOT(on_PlannerChanged(int)));
    for (auto env : _environment_list)
    {
        ui->comboBox_env_type->addItem(env);
    }
    // set to discrete environment as default
    ui->comboBox_env_type->setCurrentIndex(0); 
    for (auto planner : _planners_discrete)
    {
        ui->comboBox_planner_type->addItem(planner);
    }
    

    // Environment scene
    _env_scene = std::make_shared<EnvGraphicsScene>(this);
    ui->graphicsView->setFixedSize(960, 800);
    ui->graphicsView->setFrameStyle(0);
    ui->graphicsView->setScene(_env_scene.get()); 
    

    on_ButtonResetClicked();
    connect(_env_scene.get(), SIGNAL(MouseClicked(QGraphicsSceneMouseEvent *)), this, SLOT(on_MouseClicked(QGraphicsSceneMouseEvent *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::on_ButtonSolveClicked()
{
    std::cout << "Solving environment...\n";
    disconnect(_env_scene.get(), SIGNAL(MouseClicked(QGraphicsSceneMouseEvent *)), this, SLOT(on_MouseClicked(QGraphicsSceneMouseEvent *)));
    
    if (ui->comboBox_env_type->currentText() == "Discrete")
    {
        _env_discrete->UpdateNeighbours();
        if (ui->comboBox_planner_type->currentText() == "Depth-First Search")
        {
            std::cout << "Algorithm: Depth-First Search\n";
            // BreadthFirstSearch(_env_discrete->node_start.get(), _env_discrete->node_goal.get());
            // _env_discrete->node_start->MakeDead();
            // BreadthFirstSearch solver(_env_discrete->node_start.get(), _env_discrete->node_goal.get());
            // solver.Solve();

            std::deque<DiscreteNode *> _set_open;
            std::deque<DiscreteNode *> _set_visited;
            std::deque<DiscreteNode *> _set_camefrom;
            _set_open.push_back(_env_discrete->node_start.get());
            _set_visited.push_back(_env_discrete->node_start.get());

            while (_set_open.size() > 0)
            {
                // Get first node
                auto node_current = _set_open.front();
                // Pop it from the queue
                _set_open.pop_front();

                // Check if the current node is goal node
                if (node_current == _env_discrete->node_goal.get())
                {
                    std::cout << "Solution found.\n";
                    //TODO: draw a path
                    break;
                }
                for (auto neighbour : node_current->neighbours)
                {
                    if (std::find(_set_visited.begin(), _set_visited.end(), neighbour) == _set_visited.end())
                    {
                        _set_visited.push_back(neighbour);
                        _set_open.push_back(neighbour);
                        if (neighbour != _env_discrete->node_start.get() && neighbour != _env_discrete->node_goal.get())
                        {
                            neighbour->MakeAlive();
                        }
                    }
                    else
                    {
                    }
                    usleep(500000);
                }
                if (node_current != _env_discrete->node_start.get())
                {
                    node_current->MakeDead();
                }

            }
            std::cout << "Ending search\n";




        }
        else if (ui->comboBox_planner_type->currentText() == "Breadth-First Search")
        {
            std::cout << "Algorithm: Breadth-First Search\n";
        }
        else
        {
            std::cout << "Not implemented...\n";
        }
    }
    else if (ui->comboBox_env_type->currentText() == "Continuous")
    {

    }
    connect(_env_scene.get(), SIGNAL(MouseClicked(QGraphicsSceneMouseEvent *)), this, SLOT(on_MouseClicked(QGraphicsSceneMouseEvent *)));
}

void
MainWindow::on_ButtonResetClicked()
{
    std::cout << "Reseting environment...\n";
    if (ui->comboBox_env_type->currentText() == "Discrete")
    {
        _env_scene->clear();
        _env_discrete = std::make_shared<DiscreteEnvironment>(_WIDTH, _HEIGHT, _ROWS, _env_scene.get());
        _env_discrete->MakeGrid(_env_scene.get());
    }
    else if (ui->comboBox_env_type->currentText() == "Continuous")
    {
        _env_scene->clear();
        _env_continuous = std::make_shared<ContinuousEnvironment>(_WIDTH, _HEIGHT);
        _env_continuous->ResetEnv(_env_scene.get());
    }

}

void 
MainWindow::on_EnvironmentChanged(int env_idx)
{
    std::cout << "Environment has changed.\n";
    ui->comboBox_planner_type->clear();
    if (ui->comboBox_env_type->currentText() == "Discrete")
    {
        for (auto planner : _planners_discrete)
        {
            ui->comboBox_planner_type->addItem(planner);
        }
        _env_discrete = std::make_shared<DiscreteEnvironment>(_WIDTH, _HEIGHT, _ROWS, _env_scene.get());
    }
    else if (ui->comboBox_env_type->currentText() == "Continuous")
    {
        for (auto planner : _planners_continuous)
        {
            ui->comboBox_planner_type->addItem(planner);
        }
    }
    on_ButtonResetClicked();
}

void
MainWindow::on_PlannerChanged(int planner_idx)
{
    std::cout << "planner changed\n";
}

void
MainWindow::on_MouseClicked(QGraphicsSceneMouseEvent * mouseEvent)
{
    const auto X = mouseEvent->scenePos().x();
    const auto Y = mouseEvent->scenePos().y();
    if (ui->comboBox_env_type->currentText() == "Discrete")
    {
        auto temp_node = _env_discrete->GetMouseClickedNode(X, Y);
        if (_env_discrete->node_start == nullptr)
        {
            _env_discrete->node_start = temp_node;
            _env_discrete->node_start->MakeStart();
        }
        else if (_env_discrete->node_goal == nullptr)
        {
            if (temp_node != _env_discrete->node_start)
            {
                _env_discrete->node_goal = temp_node;
                _env_discrete->node_goal->MakeGoal();
            }
        }
        else
        {
            if (temp_node != _env_discrete->node_start &&
                temp_node != _env_discrete->node_goal &&
                !temp_node->isObstacle())
            {
                temp_node->MakeObstacle();
            }
        }
        
    }
}