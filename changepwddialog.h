#ifndef CHANGEPWDDIALOG_H
#define CHANGEPWDDIALOG_H

#include <QDialog>

namespace Ui {
class ChangePwdDialog;
}

class ChangePwdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePwdDialog(QWidget *parent = 0);
    void transmit(QString zz_User);
    ~ChangePwdDialog();

private slots:
    void on_closeBtn_clicked();

    void on_changePwdBtn_clicked();

private:
    Ui::ChangePwdDialog *ui;
    QString zz_User;
};

#endif // CHANGEPWDDIALOG_H
