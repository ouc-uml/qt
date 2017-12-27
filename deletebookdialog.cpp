#include "deletebookdialog.h"
#include "ui_deletebookdialog.h"
#include "library.h"
#include "connect.h"
#include "QStringList"
#include "errordialog.h"
#include "global.h"
#include "confirmdialog.h"
#include <iostream>
using namespace  std;

DeleteBookDialog::DeleteBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteBookDialog)
{
    ui->setupUi(this);
    ui->deleteBookTv->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->deleteBookTv->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->deleteBookTv->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

DeleteBookDialog::~DeleteBookDialog()
{
    delete ui;
}

void DeleteBookDialog::on_closeBtn_clicked()
{
    close();
}
void DeleteBookDialog::transmit(string s,int flag)
{
    zzflag = flag;
    if(zzflag == 2)
        ui->deleteBtn->setText("预约");
    this->delete_Book_id = s;

    ui->deleteBookTv->setColumnCount(3);
    clocnt =3;
    QStringList tableheader;
    tableheader<<"ISBN"<<"单本编号"<<"状态";

    ui->deleteBookTv->setHorizontalHeaderLabels(tableheader);
    ui->deleteBookTv->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    vector < vector < string > > res;
    cout<<"s :"<<s<<endl;
    cout<<"delete "<<delete_Book_id<<endl;
    res = search_Bno(delete_Book_id,1);
    cout<<"res "<<res.size()<<endl;
    ui->deleteBookTv->setRowCount(res.size()-1);
    for(int i=1;i<res.size();i++)
    {
        for(int j=0;j<res[i].size();j++)
        {
            ui->deleteBookTv->setItem(i-1,j,new QTableWidgetItem(QString::fromStdString(res[i][j])));
        }
    }

}

void DeleteBookDialog::on_deleteBtn_clicked()
{

    ErrorDialog eDlg;
    eDlg.setWindowTitle("错误提示");
    // 判断是否选中一行
    if(ui->deleteBookTv->isItemSelected(ui->deleteBookTv->currentItem()))
    {

        if(zzflag == 1)
        {
            ErrorDialog eDlg;
            eDlg.setWindowTitle("删除图书");
            int row = ui->deleteBookTv->currentItem()->row();
            string tmp = "是否删除该本图书:\n";
            QString zztmp = ui->deleteBookTv->item(row,1)->text();
            for(int i=0;i<clocnt;i++)
                tmp += ui->deleteBookTv->item(row,i)->text().toStdString() + "\n";
            ConfirmDialog cfDlg;
            cfDlg.showMsg(QString::fromStdString(tmp));
            bool ok;
            if(cfDlg.exec() == QDialog::Accepted)
            {
                cout<<"delete:"<<delete_Book_id<<endl;
                cout<<"zztmp"<<zztmp.toInt(&ok,10)<<endl;
                int zzRes = delete_book(delete_Book_id,zztmp.toInt(&ok,10));
                if(zzRes == 0)
                {
                    eDlg.showError(QString::fromStdString("删除成功"));
                    //transmit(delete_Book_id,zzflag);
                }
                else
                    eDlg.showError(QString::fromStdString("删除失败"));
                eDlg.exec();
            }
        }
        else if(zzflag == 2)
        {

            eDlg.setWindowTitle("预约图书");
            int row = ui->deleteBookTv->currentItem()->row();
            string tmp = "是否预约该本图书:\n";
            int zzeno = ui->deleteBookTv->item(row,1)->text().toInt();
            tmp += "ISBN:" + delete_Book_id + "\n";
            tmp += "单本编号:" + ui->deleteBookTv->item(row,1)->text().toStdString() + "\n";
            ConfirmDialog cfDlg;
            cfDlg.showMsg(QString::fromStdString(tmp));
            if(cfDlg.exec() == QDialog::Accepted)
            {
                int zzRes = reserve_book(delete_Book_id, zzeno, sUser, 14);
                cout<<"zzRes = "<<zzRes<<endl;
                if(zzRes == 0)
                    eDlg.showError(QString::fromStdString("预约成功"));
                else if(zzRes == 1)
                    eDlg.showError(QString::fromStdString("保存本"));
                else if(zzRes == 2)
                    eDlg.showError(QString::fromStdString("非保存本在馆"));
                else if(zzRes == 4)
                    eDlg.showError(QString::fromStdString("已被预约"));
                else
                    eDlg.showError(QString::fromStdString("无法预约"));
                eDlg.exec();
            }
        }
    }
    else
    {
        eDlg.showError(QString::fromStdString("没有选中"));
        eDlg.exec();
    }
}
