#include "newdldialog.h"
#include "ui_newdldialog.h"

NewDLDialog::NewDLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDLDialog)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

NewDLDialog::~NewDLDialog()
{
    delete ui;
}
