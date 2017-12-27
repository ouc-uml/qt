#ifndef SENDMSGDIALOG_H
#define SENDMSGDIALOG_H

#include <QDialog>

namespace Ui {
class sendMsgDialog;
}

class sendMsgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sendMsgDialog(QWidget *parent = 0);
    ~sendMsgDialog();

private slots:
    void on_confirmBtn_clicked();

    void on_sendBtn_clicked();

private:
    Ui::sendMsgDialog *ui;
};

#endif // SENDMSGDIALOG_H
