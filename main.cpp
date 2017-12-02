#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *main = new MainWindow;
    LoginDialog *logindlg = new LoginDialog;
    if(logindlg->exec() == QDialog::Accepted )
    {
        if(user_Type==0){
            main->showNormalUser();
            main->show();
            return a.exec();
        }
        else
        {
            main->showAdministrator();
            main->show();
            return a.exec();
        }
    }
}
