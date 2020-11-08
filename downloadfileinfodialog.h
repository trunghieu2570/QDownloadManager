#ifndef DOWNLOADFILEINFODIALOG_H
#define DOWNLOADFILEINFODIALOG_H

#include "paralleldownload.h"
#include "remotefileinfo.h"

#include <QDialog>
#include <QRandomGenerator>

namespace Ui {
class DownloadFileInfoDialog;
}

class DownloadFileInfoDialog : public QDialog
{
    Q_OBJECT

public:
    static DownloadFileInfoDialog *createInstance(RemoteFileInfo *);
    ~DownloadFileInfoDialog();
    RemoteFileInfo *getRemoteFileInfo() const;
public slots:
    void showDialog();
private:
    Ui::DownloadFileInfoDialog *ui;
    explicit DownloadFileInfoDialog(QWidget *parent = nullptr);
    RemoteFileInfo * rfInfo;
signals:
    void startButtonClicked(BaseDownload *dl);
};

#endif // DOWNLOADFILEINFODIALOG_H
