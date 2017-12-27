#include "sendmsgdialog.h"
#include "ui_sendmsgdialog.h"
#include <string>
#include "library.h"
#include <vector>
#include "global.h"
#include "errordialog.h"

using namespace std;

sendMsgDialog::sendMsgDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sendMsgDialog)
{
    ui->setupUi(this);
    ui->nameLe->setMaxLength(10);
}

sendMsgDialog::~sendMsgDialog()
{
    delete ui;
}

void sendMsgDialog::on_confirmBtn_clicked()
{
    string zzUser = ui->nameLe->text().toStdString();
    if(zzUser.size()==0)
    {
        ErrorDialog eDlg;
        eDlg.setWindowTitle("错误提示");
        eDlg.showError(QString::fromStdString("请输入查询条件"));
        eDlg.exec();
    }
    else
    {
        vector<string> res;
        res = user_info(zzUser);
        string tmp;
        for(int i=0;i<res.size();i++)
        {
            tmp += res[i] + "\n";
        }
        if(res.size())
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("信息查询");
            eDlg.showError(QString::fromStdString(tmp));
            eDlg.exec();
        }
        else
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("信息查询");
            eDlg.showError(QString::fromStdString("没有此用户"));
            eDlg.exec();
        }
    }
}

void sendMsgDialog::on_sendBtn_clicked()
{
    string zzUser = ui->nameLe->text().toStdString();
    if(zzUser.size()==0)
    {
        ErrorDialog eDlg;
        eDlg.setWindowTitle("错误信息");
        eDlg.showError(QString::fromStdString("用户名为空"));
        eDlg.exec();
    }
    else
    {
        vector<string> res;
        res = user_info(zzUser);
        if(res.size()==0)
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("信息查询");
            eDlg.showError(QString::fromStdString("没有此用户"));
            eDlg.exec();
        }
        else
        {
            string zzText = ui->msgTe->toPlainText().toStdString();
            if(zzText.size()==0)
            {
                ErrorDialog eDlg;
                eDlg.setWindowTitle("错误信息");
                eDlg.showError(QString::fromStdString("信息为空"));
                eDlg.exec();
            }
            else
            {
                int zzRes=  send_message(sUser,zzUser,zzText);
                if(zzRes==0)
                {
                    ErrorDialog eDlg;
                    eDlg.setWindowTitle("发送信息");
                    eDlg.showError(QString::fromStdString("发送成功"));
                    eDlg.exec();
                }
                else
                {
                    ErrorDialog eDlg;
                    eDlg.setWindowTitle("发送信息");
                    eDlg.showError(QString::fromStdString("发送失败"));
                    eDlg.exec();
                }
            }
        }
    }
}
