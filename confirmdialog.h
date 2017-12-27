#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>
#include <string>
using namespace std;

namespace Ui {
class ConfirmDialog;
}

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDialog(QWidget *parent = 0);
    ~ConfirmDialog();
    void showMsg(QString msg);
    void import_data(string zzspath);
    void transmit(int zzflag);


private slots:
    void on_closeBtn_clicked();

    void on_confirmBtn_clicked();

private:
    Ui::ConfirmDialog *ui;
    int zz;
    string zzspath;
    int zzcnt;
};

#endif // CONFIRMDIALOG_H
