#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include "global.h"
#include "connect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *main = new MainWindow;
    LoginDialog *logindlg = new LoginDialog;
    if(logindlg->exec() == QDialog::Accepted )
    {
        if(user_rank<6)
            main->showAdministrator();
        else
        {
            main->showNormalUser();
           // main->recMsg();
        }
        main->show();
        return a.exec();
    }
}
