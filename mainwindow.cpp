#include "downloadmodel.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

BaseDownload *MainWindow::getCurrentDownload() const
{
    return currentDownload;
}

void MainWindow::setCurrentDownload(BaseDownload *value)
{
    currentDownload = value;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAddURL, &QAction::triggered, this, &MainWindow::openAddURLDialog);
    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::openOptionsDialog);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quitApplication);

    downloadManager = DownloadManager::getInstance();
    QList<BaseDownload *> *list = downloadManager->getDownloadList();

    QString add = "https://download.virtualbox.org/virtualbox/6.1.14/VirtualBox-6.1.14-140239-Win.exe";
    QUrl url = QUrl::fromEncoded(add.toLocal8Bit());
    BaseDownload * dl = new ParallelDownload();
    dl->setAddress(url);
    dl->setName("hello.exe");

    list->append(dl);

    DownloadModel * model = new DownloadModel;
    ui->downloadTableView->setModel(model);
    QItemSelectionModel * slmd = ui->downloadTableView->selectionModel();
    connect(slmd, &QItemSelectionModel::selectionChanged, this, &MainWindow::downloadListSelectionChanged);
    model->populate();
    connect(dl, &BaseDownload::stateChanged, model, &DownloadModel::populate);
    //dl->start();

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

void MainWindow::downloadTableSelected()
{
    //qDebug() << ui->downloadTableWidget->selectedItems().size();
}

void MainWindow::downloadListSelectionChanged(QItemSelection selected, QItemSelection deselected)
{
    QList<BaseDownload *> *list = downloadManager->getDownloadList();
    currentDownload = list->at(selected.indexes().);
    qDebug() << selected.size();
}

