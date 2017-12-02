#include "torecdialog.h"
#include "ui_torecdialog.h"

toRecDialog::toRecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::toRecDialog)
{
    ui->setupUi(this);
}

toRecDialog::~toRecDialog()
{
    delete ui;
}

void toRecDialog::on_closeBtn_clicked()
{
    close();
}
