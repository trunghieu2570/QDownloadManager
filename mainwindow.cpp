#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAddURL, &QAction::triggered, this, &MainWindow::openAddURLDialog);
    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::openOptionsDialog);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quitApplication);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openAddURLDialog()
{
    NewDLDialog *dialog = new NewDLDialog();
    dialog->show();
}

void MainWindow::openOptionsDialog()
{
    OptionsDialog *dialog = new OptionsDialog();
    dialog->show();
}

void MainWindow::quitApplication()
{
    QCoreApplication::quit();
}

