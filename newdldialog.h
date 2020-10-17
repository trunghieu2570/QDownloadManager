#ifndef NEWDLDIALOG_H
#define NEWDLDIALOG_H

#include <QDialog>

namespace Ui {
class NewDLDialog;
}

class NewDLDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDLDialog(QWidget *parent = nullptr);
    ~NewDLDialog();

private:
    Ui::NewDLDialog *ui;
};

#endif // NEWDLDIALOG_H
