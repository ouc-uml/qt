#ifndef STUBORDIALOG_H
#define STUBORDIALOG_H

#include <QDialog>
#include <string>
using namespace std;
namespace Ui {
class StuBorDialog;
}

class StuBorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StuBorDialog(QWidget *parent = 0);
    ~StuBorDialog();
    void transmit(int zzFlag,string zzStuId);

private slots:
    void on_closeBtn_clicked();

private:
    Ui::StuBorDialog *ui;
    int flag;
    string stuId;
};

#endif // STUBORDIALOG_H
