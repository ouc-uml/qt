#include "stubordialog.h"
#include "ui_stubordialog.h"
#include "library.h"

StuBorDialog::StuBorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StuBorDialog)
{
    ui->setupUi(this);
    QStringList tableheader;
    tableheader<<"用户名"<<"ISBN"<<"单本编号"<<"借阅时间"<<"持续时间"<<"状态";
    ui->showBorTw->setColumnCount(6);
    ui->showBorTw->setHorizontalHeaderLabels(tableheader);
    ui->showBorTw->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);


}

StuBorDialog::~StuBorDialog()
{
    delete ui;
}

void StuBorDialog::transmit(int zzFlag, string zzStuId)
{
    flag = zzFlag;
    stuId = zzStuId;
    vector < vector < string > > res;
    if(flag == 1)
    {
        res = reader_history (stuId);
        ui->showBorTw->setRowCount(res.size()-1);
        for(int i=1;i<res.size();i++)
        {
            for(int j=0;j<res[i].size();j++)
            {
                ui->showBorTw->setItem(i-1,j,new QTableWidgetItem(QString::fromStdString(res[i][j])));
            }
        }
    }
    else if(flag == 2)
    {
        res = reader_current (stuId);
        ui->showBorTw->setRowCount(res.size()-1);
        for(int i=1;i<res.size();i++)
        {
            for(int j=0;j<res[i].size();j++)
            {
                ui->showBorTw->setItem(i-1,j,new QTableWidgetItem(QString::fromStdString(res[i][j])));
            }
        }
    }
}

void StuBorDialog::on_closeBtn_clicked()
{
    close();
}
