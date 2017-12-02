#include "logindialog.h"
#include "ui_logindialog.h"
#include "global.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

int LoginDialog::on_loginBtn_clicked()
{
    user_Type =ui->userTypeCb->currentIndex();
    accept();
}
