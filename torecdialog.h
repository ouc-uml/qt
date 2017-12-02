#ifndef TORECDIALOG_H
#define TORECDIALOG_H

#include <QDialog>

namespace Ui {
class toRecDialog;
}

class toRecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit toRecDialog(QWidget *parent = 0);
    ~toRecDialog();

private slots:
    void on_closeBtn_clicked();

private:
    Ui::toRecDialog *ui;
};

#endif // TORECDIALOG_H
