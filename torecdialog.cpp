#include "torecdialog.h"
#include "ui_torecdialog.h"
#include <string>
#include "errordialog.h"
#include "global.h"
#include "library.h"
using namespace std;
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

void toRecDialog::on_toRecBtn_clicked()
{
    string sBno = ui->BnoLe->text().toStdString();
    string sBname = ui->BnameLe->text().toStdString();
    if(sBno.size() == 0 || sBname.size() ==0 )
    {
        ErrorDialog eDlg;
        eDlg.setWindowTitle("错误信息");
        eDlg.showError("信息不能为空");
        eDlg.exec();
        return;
    }
    string res = recommend(sBno,sBname,sUser);
    ErrorDialog eDlg;
    eDlg.setWindowTitle("荐购信息");
    eDlg.showError(QString::fromStdString(res));
    /*
    if(res == "推荐成功")
        eDlg.showError(QString::fromStdString("荐购成功"));
    else
        eDlg.showError(QString::fromStdString("荐购失败"));
        */
    eDlg.exec();
}
