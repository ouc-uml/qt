#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <vector>
using namespace std ;

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = 0);
    void transmit1(int zztmp1);
    void transmit2(vector<string>zzv1);
    ~AddBookDialog();

private slots:
    void on_addBtn_clicked();


private:
    Ui::AddBookDialog *ui;
    int zzflag1;
    vector<string> zzv;
};

#endif // ADDBOOKDIALOG_H
