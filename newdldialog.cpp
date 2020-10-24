#include "newdldialog.h"
#include "ui_newdldialog.h"

NewDLDialog::NewDLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDLDialog)
{
    ui->setupUi(this);

    //set fixed window size
    this->setFixedSize(this->width(), this->height());

    //connect OK/Cancel button to dialog slots;
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &NewDLDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &NewDLDialog::reject);
}

NewDLDialog::~NewDLDialog()
{
    delete ui;
}

QString NewDLDialog::getUrl()
{
    return ui->lineEdit->text();
}
