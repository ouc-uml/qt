#include "addstudialog.h"
#include "ui_addstudialog.h"
#include "library.h"
#include <string>
#include <vector>
#include "connect.h"
#include "errordialog.h"
#include "md5.h"
#include "global.h"
#include <time.h>
using namespace std;
addStuDialog::addStuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addStuDialog)
{
    ui->setupUi(this);
    if(user_rank != 1)
        delete ui->typeCb;
}

addStuDialog::~addStuDialog()
{
    delete ui;
}

void addStuDialog::on_pushButton_2_clicked()
{
    close();
}

void addStuDialog::on_pushButton_clicked()
{
    if(zzflag1 == 1)
    {
        std::string zzUser = ui->userLe->text().toStdString();
        std::string zzPwd = ui->pwdLe->text().toStdString();
        std::string zzNick = ui->nickLe->text().toStdString();
        std::string zzAge = ui->ageLe->text().toStdString();
        if(zzUser.size()==0 || zzPwd.size() == 0 || zzNick.size() == 0 || zzAge.size() == 0)
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("错误提示");
            eDlg.showError(QString::fromStdString("请完整输入信息"));
            eDlg.exec();
            return ;
        }
        for(int i=0;i<zzAge.size();i++)
        {
            if(zzAge[i]<'0' || zzAge[i] >'9')
            {
                ErrorDialog eDlg;
                eDlg.setWindowTitle("错误提示");
                eDlg.showError(QString::fromStdString("年龄输入错误"));
                eDlg.exec();
                return ;
            }
        }
        std::vector <std::string> tmp;
        tmp.push_back(zzUser);
        MD5 md5(zzPwd);
        string zzzpwd=md5.hexdigest();
        tmp.push_back(zzzpwd);
        if(user_rank!=1)
        {
            cout<<"2   6"<<endl;
            tmp.push_back("6");
        }
        else
        {
            int zzff = ui->typeCb->currentIndex();
            if(zzff == 0)
            {
                cout<<"1   2"<<endl;
                tmp.push_back("2");
            }
            else
            {
                cout<<"1   6"<<endl;
                tmp.push_back("6");
            }
        }
        tmp.push_back(zzNick);
        tmp.push_back(zzAge);

        ErrorDialog eDlg;
        eDlg.setWindowTitle("插入学生");
        int zzRes = add_user(tmp);
        if( zzRes  ==0)
            eDlg.showError("插入成功");
        else if(zzRes == 1)
            eDlg.showError("未知错误");
        else if(zzRes == 2)
            eDlg.showError("没有权限");
        else if(zzRes == 3)
            eDlg.showError("已存在");
        else
            eDlg.showError("插入失败");
        eDlg.exec();
    }
    else if(zzflag1 == 2)
    {
        std::string zzUser = ui->userLe->text().toStdString();
        std::string zzNick = ui->nickLe->text().toStdString();
        std::string zzAge = ui->ageLe->text().toStdString();
        int zzstate = ui->stateCb->currentIndex();
        if(zzUser.size()==0 || zzNick.size() == 0 || zzAge.size() == 0)
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("错误提示");
            eDlg.showError(QString::fromStdString("请完整输入信息"));
            eDlg.exec();
            return ;
        }
        std::string zzState = "";
        stringstream ss;
        ss.clear();
        ss<<zzstate;
        ss>>zzState;
        std::vector <std::string> tmp;
        tmp.push_back(zzUser);
        tmp.push_back(zzState);
        tmp.push_back(zzNick);
        tmp.push_back(zzAge);
        ErrorDialog eDlg;
        eDlg.setWindowTitle("修改信息");
        int zzRes = update_user(tmp);
        if( zzRes  ==0)
            eDlg.showError("修改成功");
        else if(zzRes == 1)
            eDlg.showError("未知错误");
        else if(zzRes == -2)
            eDlg.showError("没有权限");
        else if(zzRes == 3)
            eDlg.showError("已存在");
        else
            eDlg.showError("插入错误");
        eDlg.exec();
    }


}

void addStuDialog::transmit1(int zztmp1)
{
    this->zzflag1 = zztmp1;
    if(this->zzflag1==1)
    {
        delete ui->stateCb;
    }
    if(this->zzflag1==2)
    {
        ui->userLe->setEnabled(false);
        ui->pushButton->setText("修改");
    }
}

void addStuDialog::transmit2(vector<string>zzv1)
{
    for(int i=0;i<zzv1.size();i++)
        zzv.push_back(zzv1[i]);
    ui->userLe->setText(QString::fromStdString(zzv1[0]));
    int zzRank = 0;
    user_lev(zzv1[0],zzRank);
    if(zzRank == 2)
        ui->stateCb->setEnabled(false);
    else
    {
        if(zzv1[1] == "0")
            ui->stateCb->setCurrentIndex(0);
        else
            ui->stateCb->setCurrentIndex(1);
    }
    delete ui->pwdLb;
    delete ui->pwdLe;
    delete ui->typeCb;
    ui->nickLe->setText(QString::fromStdString(zzv1[2]));
    ui->ageLe->setText(QString::fromStdString(zzv1[3]));
}
