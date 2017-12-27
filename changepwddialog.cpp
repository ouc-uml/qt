#include "changepwddialog.h"
#include "ui_changepwddialog.h"
#include "connect.h"
#include "errordialog.h"

ChangePwdDialog::ChangePwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePwdDialog)
{
    ui->setupUi(this);
    ui->oldPwd->setMaxLength(16);
    ui->newPwd->setMaxLength(16);
    ui->checkNewPwd->setMaxLength(16);
    ui->oldPwd->setEchoMode(QLineEdit::Password);
    ui->newPwd->setEchoMode(QLineEdit::Password);
    ui->checkNewPwd->setEchoMode(QLineEdit::Password);

}

ChangePwdDialog::~ChangePwdDialog()
{
    delete ui;
}
void ChangePwdDialog::transmit(QString zz_User)
{
    this->zz_User = zz_User;
}

void ChangePwdDialog::on_closeBtn_clicked()
{
    close();
}

void ChangePwdDialog::on_changePwdBtn_clicked()
{
    QString qs_old_pwd = ui->oldPwd->text();
    QString qs_new_pwd= ui->newPwd->text();
    QString qs_check_new_pwd = ui->checkNewPwd->text();
    if(qs_check_new_pwd!=qs_new_pwd)
    {
        ErrorDialog eDlg;
        eDlg.setWindowTitle("更改密码");
        eDlg.showError("两次新密码不一样");
        eDlg.exec();
    }
    else
    {
        int zz_Res = change_pwd(qs_old_pwd.toStdString(),qs_new_pwd.toStdString());
        if(zz_Res==0)
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("更改密码");
            eDlg.showError("修改成功");
            eDlg.exec();
        }
        else
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("更改密码");
            eDlg.showError("修改失败");
            eDlg.exec();
        }
    }
}
