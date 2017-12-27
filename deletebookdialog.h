#ifndef DELETEBOOKDIALOG_H
#define DELETEBOOKDIALOG_H

#include <QDialog>
#include <string>

using namespace std ;

namespace Ui {
class DeleteBookDialog;
}

class DeleteBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteBookDialog(QWidget *parent = 0);
    ~DeleteBookDialog();
    void transmit(string s,int flag);

private slots:
    void on_closeBtn_clicked();
    void on_deleteBtn_clicked();

private:
    Ui::DeleteBookDialog *ui;
    string delete_Book_id;
    int clocnt;
    int zzflag;
};

#endif // DELETEBOOKDIALOG_H
