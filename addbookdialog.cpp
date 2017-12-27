#include "addbookdialog.h"
#include "ui_addbookdialog.h"
#include <string>
#include "global.h"
#include "errordialog.h"
#include "sstream"
#include "connect.h"
#include "library.h"
using namespace std;

AddBookDialog::AddBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBookDialog)
{
    ui->setupUi(this);
}

AddBookDialog::~AddBookDialog()
{

    delete ui;
}

void AddBookDialog::on_addBtn_clicked()
{
    stringstream ss;
    if(zzflag1 == 1)//加书
    {
        string Bno = ui->ISBNLe->text().toStdString();
        string Eno = ui->EnoLe->text().toStdString();
        for(int i=0;i<Eno.size();i++)
        {
            if(Eno[i]<'0' || Eno[i] >'9')
            {
                ErrorDialog eDlg;
                eDlg.setWindowTitle("错误提示");
                eDlg.showError(QString::fromStdString("书号不能为负数"));
                eDlg.exec();
                return ;
            }
        }
        string name = ui->nameLe->text().toStdString();
        string type = ui->typeLe->text().toStdString();
        string author = ui->authorLe->text().toStdString();
        string press = ui->pressLe->text().toStdString();
        int tmp = ui->saveCb->currentIndex();
        string save;
        tmp++;
        cout<<"tmp"<<tmp<<endl;
        ss.clear();
        ss<<tmp;
        ss>>save;
        if(Bno.size() == 0 || Eno.size() == 0||name.size() ==0 || type.size()==0 || author.size()==0|| press.size()==0)
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("错误提示");
            eDlg.showError(QString::fromStdString("请输入完整信息"));
            eDlg.exec();
            return ;
        }
        vector<string>newbook;
        newbook.push_back(Bno);
        newbook.push_back(Eno);
        newbook.push_back(save);
        newbook.push_back(name);
        newbook.push_back(type);
        newbook.push_back(author);
        newbook.push_back(press);
        ErrorDialog eDlg;
        eDlg.setWindowTitle("插入提示");

        int zzRes= add_book(sUser,newbook);
        if(zzRes ==0)
            eDlg.showError(QString::fromStdString("插入成功"));
        else if(zzRes == 1)
             eDlg.showError(QString::fromStdString("已存在"));
        else if(zzRes == 2)
             eDlg.showError(QString::fromStdString("没有权限"));
        else
            eDlg.showError(QString::fromStdString("插入错误"));
        eDlg.exec();
    }
    else if(zzflag1 == 2)//update书
    {
        string Bno = ui->ISBNLe->text().toStdString();
        string name = ui->nameLe->text().toStdString();
        string type = ui->typeLe->text().toStdString();
        string author = ui->authorLe->text().toStdString();
        string press = ui->pressLe->text().toStdString();
        if(Bno.size() == 0 ||name.size() ==0 || type.size()==0 || author.size()==0|| press.size()==0)
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("错误提示");
            eDlg.showError(QString::fromStdString("请输入完整信息"));
            eDlg.exec();
            return ;
        }
        vector<string>newbook;
        newbook.push_back(Bno);
        newbook.push_back(zzv[2]);
        newbook.push_back(name);
        newbook.push_back(type);
        newbook.push_back(author);
        newbook.push_back(press);
        //
        for(int i=0;i<newbook.size();i++)
            cout<<newbook[i]<<endl;
        //
        ErrorDialog eDlg;
        eDlg.setWindowTitle("修改提示");
        int zzRes= update_book(newbook);
        if(zzRes ==0)
            eDlg.showError(QString::fromStdString("修改成功"));
        /*
    else if(zzRes == 1)
        eDlg.showError(QString::fromStdString("已存在"));
    else if(zzRes == 2)
        eDlg.showError(QString::fromStdString("没有权限"));
        */
        else
            eDlg.showError(QString::number(zzRes,10));
        eDlg.exec();
    }
}

void AddBookDialog::transmit1(int zztmp1)
{
    this->zzflag1 = zztmp1;
    if(this->zzflag1==2)
        ui->addBtn->setText("修改");
}

void AddBookDialog::transmit2(vector<string>zzv1)
{
    for(int i=0;i<zzv1.size();i++)
        zzv.push_back(zzv1[i]);

    ui->ISBNLe->setText(QString::fromStdString(zzv1[0]));
    ui->ISBNLe->setEnabled(false);
    delete ui->EnoLe;
    delete ui->EnoLB;
    delete ui->saveCb;
    ui->nameLe->setText(QString::fromStdString(zzv1[3]));
    ui->typeLe->setText(QString::fromStdString(zzv1[4]));
    ui->authorLe->setText(QString::fromStdString(zzv1[5]));
    ui->pressLe->setText(QString::fromStdString(zzv1[6]));
}

