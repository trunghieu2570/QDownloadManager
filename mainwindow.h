#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelection>
#include <QMainWindow>
#include "newdldialog.h"
#include "optionsdialog.h"
#include "downloadmanager.h"
#include "paralleldownload.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    DownloadManager *downloadManager;
    BaseDownload *currentDownload = nullptr;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    BaseDownload *getCurrentDownload() const;
    void setCurrentDownload(BaseDownload *value);

private slots:
    void openAddURLDialog();
    void openOptionsDialog();
    void quitApplication();
    void downloadTableSelected();
    void downloadListSelectionChanged(QItemSelection selected, QItemSelection deselected);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
