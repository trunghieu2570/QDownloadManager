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
    //connect actions
    connect(ui->actionAddURL, &QAction::triggered, this, &MainWindow::openAddURLDialog);
    connect(ui->actionOptions, &QAction::triggered, this, &MainWindow::openOptionsDialog);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quitApplication);
    //get download manager instance
    downloadManager = DownloadManager::getInstance();
    //setup download list table models
    downloadModel = new DownloadModel;
    ui->downloadTableView->setModel(downloadModel);
    slmd = ui->downloadTableView->selectionModel();
    connect(slmd, &QItemSelectionModel::selectionChanged, this, &MainWindow::downloadListSelectionChanged);
    downloadModel->populate();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openAddURLDialog()
{
    NewDLDialog *dialog = new NewDLDialog();
    if (dialog->exec() == QDialog::Accepted) {
        //if Ok button was clicked
        QString add = dialog->getUrl();
        QUrl url = QUrl::fromEncoded(add.toLocal8Bit());
        BaseDownload * dl = new ParallelDownload();
        dl->setAddress(url);
//        dl->setName(QString("file").append(QString::number(QRandomGenerator::global()->generate())).append(".exe"));
        dl->setName(QString("file").append(".exe"));
        downloadManager->addDownload(dl);
        downloadModel->populate();
        dl->loadInfo();
        dl->start();
    }
}

void MainWindow::openOptionsDialog()
{
    OptionsDialog *dialog = new OptionsDialog();
    dialog->show();
}

void MainWindow::resumeDownload()
{
    foreach (auto _i, slmd->selectedIndexes()) {
        QList<BaseDownload *> list = downloadManager->getDownloadList();
        BaseDownload *_c = list.at(_i.row());
        _c->start();
    }
}

void MainWindow::pauseDownload()
{

}

void MainWindow::quitApplication()
{
    QCoreApplication::quit();
}

void MainWindow::downloadListSelectionChanged(QItemSelection selected, QItemSelection deselected)
{
    //disconnect signals and delete old table
    if (segmentModel) {
        segmentModel->deleteLater();
        segmentModel = nullptr;
    }
    //hide if none is selected
    if(slmd->selectedIndexes().size() <= 0) {
        ui->tabWidget->hide();
        return;
    } else {
        ui->tabWidget->show();
    }


    QList<BaseDownload *> list = downloadManager->getDownloadList();
    currentDownload = list.at(slmd->selectedIndexes().first().row());

    if (currentDownload)
    {
        if(currentDownload->getType() == DownloadType::PARALLEL_DOWNLOAD) {
            ui->currentTaskLabel->setText(currentDownload->getName());
            ParallelDownload *_prld = dynamic_cast<ParallelDownload*>(currentDownload);

            //setup segment list table models
            segmentModel = new SegmentModel;
            ui->segProgressTableView->setModel(segmentModel);
            segmentModel->populate(_prld);

            QList<Segment*> _segList = _prld->getSegmentList();
            QLayout *_layout =  ui->segProgressBarFrame->layout();
            QLayoutItem *_child;
            //clear all children;
            while ((_child = _layout->takeAt(0)) != 0)  {
                if (_child->widget())
                    _child->widget()->deleteLater();
                delete _child;
            }

            for(int i = 0; i < _segList.size(); i++) {
                //create a progressbar
                auto _seg = _segList.at(i);
                QProgressBar *bar = new QProgressBar(ui->segProgressBarFrame);
                bar->setTextVisible(false);
                bar->setMinimumWidth(1);
                //set the initial value
                bar->setMaximum(100);
                bar->setValue(_seg->getReceivedSize() * 100 / _seg->getTotalSize());
                //update progressbar value
                connect(_seg, &Segment::segmentProgressChanged, bar, [=](qint64 rev, qint64 total) {
                    bar->setValue(rev*100/total);
                });
                //add progressbar to layout and show
                _layout->addWidget(bar);
                bar->setStyleSheet("QProgressBar:horizontal {\nborder: 0px solid gray;\nborder-radius: 0px;\nborder-right: 1px solid gray;\nbackground: white;\npadding: 0px;\ntext-align: right;\n}\nQProgressBar::chunk:horizontal {\nbackground: blue;\nmargin-right: 0px; /* space */\nwidth: 10px;\n}");
                bar->show();
            }
        }
    }
}

