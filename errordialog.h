#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include "library.h"

namespace Ui {
class ErrorDialog;
}

class ErrorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorDialog(QWidget *parent = 0);
    ~ErrorDialog();
    void showError(QString Error);


private slots:
    void on_closeBtn_clicked();

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
