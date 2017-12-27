#include "confirmdialog.h"
#include "ui_confirmdialog.h"
#include "library.h"
#include "errordialog.h"
#include "global.h"
#include <sstream>

ConfirmDialog::ConfirmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmDialog)
{
    ui->setupUi(this);
    this->zz = 0;
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}

void ConfirmDialog::showMsg(QString msg)
{
    ui->confirmLb->setText(msg);
}

void ConfirmDialog::on_closeBtn_clicked()
{
    close();
}

void ConfirmDialog::on_confirmBtn_clicked()
{
    if(zz == 0)
        accept();
    else if(zz == 1)
    {
        //delete ui->confirmBtn;
        //ui->confirmLb->setText("正在导入，请勿操作，后果自负");
        string zzRes = add_books(zzspath, sUser,zzcnt);
        if(zzRes == "导入成功")
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("导入图书");
            string tmp = "导入成功\n共导入";
            stringstream ss;
            ss.clear();
            string gouzi;
            ss<<zzcnt;
            ss>>gouzi;
            tmp += gouzi + "本\n";
            eDlg.showError(QString::fromStdString(tmp));
            eDlg.exec();
        }
        else
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("导入图书");
            eDlg.showError(QString::fromStdString(zzRes));
            eDlg.exec();
        }
        close();
    }
    else if(zz == 2)
    {
        //delete ui->confirmBtn;
        //ui->confirmLb->setText("正在导入，请勿操作，后果自负");
        cout<<"zzzzzzzzzzzzzzzzzzz"<<endl;
        string zzRes = add_users(zzspath,zzcnt);
        if(zzRes == "导入成功")
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("导入用户");
            string tmp = "导入成功\n共导入";
            stringstream ss;
            ss.clear();
            string gouzi;
            ss<<zzcnt;
            ss>>gouzi;
            tmp += gouzi + "人\n";
            eDlg.showError(QString::fromStdString(tmp));
            eDlg.exec();
        }
        else
        {
            cout<<"asdfasdf"<<endl;
            ErrorDialog eDlg;
            eDlg.setWindowTitle("导入用户");
            eDlg.showError(QString::fromStdString(zzRes));
            eDlg.exec();
        }
        close();
    }
}
void ConfirmDialog::import_data(string zzspath)
{
    this->zzspath = zzspath;
}
void ConfirmDialog::transmit(int zzflag)
   {
       this->zz = zzflag;
   }
