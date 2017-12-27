#include "logindialog.h"
#include "ui_logindialog.h"
#include "global.h"
#include "library.h"
#include "connect.h"

#include <sstream>
#include <string>
#include "errordialog.h"

using namespace  std;
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->userLe->setMaxLength(16);
    ui->pwdLe->setEchoMode(QLineEdit::Password);
    ui->pwdLe->setMaxLength(16);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

int LoginDialog::on_loginBtn_clicked()
{
    QString qsUser =ui->userLe->text();
    QString qsPwd = ui->pwdLe->text();
    if(qsUser.size()==0 || qsPwd.size()==0)
    {
        ErrorDialog eDlg;
        eDlg.setWindowTitle("错误提示");
        eDlg.showError(QString::fromStdString("请输入完整信息"));
        eDlg.exec();
        return -10000;
    }
    sUser.clear();
    sPwd.clear();
    sUser = qsUser.toStdString();
    sPwd = qsPwd.toStdString();
    int login_res = login(sUser,sPwd);

    if(login_res >0 && login_res < 7)
    {
        user_rank = login_res;

        accept();
    }
    else
    {
        ErrorDialog eDlg;
        if(login_res == -1)
            eDlg.showError(QString::fromStdString("密码或账号错误"));
        else if(login_res == -3)
            eDlg.showError(QString::fromStdString("网络错误"));
        else
            eDlg.showError(QString::fromStdString("登录失败"));
        eDlg.setWindowTitle("错误提示");
        eDlg.exec();
    }
}
