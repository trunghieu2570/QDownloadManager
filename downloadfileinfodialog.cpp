#include "downloadfileinfodialog.h"
#include "ui_downloadfileinfodialog.h"

DownloadFileInfoDialog::DownloadFileInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadFileInfoDialog)
{
    ui->setupUi(this);
    connect(ui->startButton, &QPushButton::clicked, this, &DownloadFileInfoDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &DownloadFileInfoDialog::reject);
}

RemoteFileInfo *DownloadFileInfoDialog::getRemoteFileInfo() const
{
    return rfInfo;
}

DownloadFileInfoDialog *DownloadFileInfoDialog::createInstance(RemoteFileInfo *rf)
{
    DownloadFileInfoDialog * r = new DownloadFileInfoDialog();
    r->rfInfo = rf;
    connect(r->rfInfo, &RemoteFileInfo::done, r, &DownloadFileInfoDialog::showDialog);
    rf->startFetching();
    return r;
}

DownloadFileInfoDialog::~DownloadFileInfoDialog()
{
    delete ui;
}

void DownloadFileInfoDialog::showDialog()
{
    disconnect(rfInfo, &RemoteFileInfo::done, this, &DownloadFileInfoDialog::showDialog);
    ui->urlLineEdit->setText(rfInfo->getAddress());
    QLocale locale = QLocale::system();
    ui->sizeLabel->setText(locale.formattedDataSize(rfInfo->getSize()));
    ui->saveAsComboBox->setCurrentText(QString("file").append(QString::number(QRandomGenerator::global()->generate())).append(".exe"));
    if(this->exec() == Accepted)
    {
        ParallelDownload * dl = new ParallelDownload();
        dl->setRemoteInfo(rfInfo);
        dl->setAddress(rfInfo->getAddress());
        dl->setName(ui->saveAsComboBox->currentText());
        dl->setSize(rfInfo->getSize());
        emit startButtonClicked(dl);
        this->deleteLater();
    }
    else
        this->deleteLater();
}
