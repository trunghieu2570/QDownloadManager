#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "newdldialog.h"
#include "optionsdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openAddURLDialog();
    void openOptionsDialog();
    void quitApplication();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
