#ifndef ADDSTUDIALOG_H
#define ADDSTUDIALOG_H

#include <QDialog>
#include <vector>
using namespace std ;

namespace Ui {
class addStuDialog;
}

class addStuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addStuDialog(QWidget *parent = 0);
    void transmit1(int zztmp1);
    void transmit2(vector<string>zzv1);
    ~addStuDialog();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::addStuDialog *ui;
    int zzflag1;
    vector<string> zzv;
};

#endif // ADDSTUDIALOG_H
