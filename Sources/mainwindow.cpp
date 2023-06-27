#include "mainwindow.h"
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
    _env_scene = new QGraphicsScene(this);
    ui->graphicsView->setFixedSize(960, 800);
    ui->graphicsView->setFrameStyle(0);
    ui->graphicsView->setScene(_env_scene); 
    

    on_ButtonResetClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::on_ButtonSolveClicked()
{
    std::cout << "Solving environment...\n";

}

void
MainWindow::on_ButtonResetClicked()
{
    std::cout << "Reseting environment...\n";
    if (ui->comboBox_env_type->currentText() == "Discrete")
    {
        
        _env_discrete = new DiscreteEnvironment(_WIDTH, _HEIGHT, _ROWS);
        _env_discrete->MakeGrid(_env_scene);
    }
    else if (ui->comboBox_env_type->currentText() == "Continuous")
    {
    
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
        _env_discrete = new DiscreteEnvironment(_WIDTH, _HEIGHT, _ROWS);


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