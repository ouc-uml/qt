#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    //普通用户的界面
    QVBoxLayout *mainLayout;
    QHBoxLayout *toplayout;
    QHBoxLayout *midlayout;
    QHBoxLayout *botlayout;
    QVBoxLayout *leftlayout;
    QVBoxLayout *rightlayout;
    QWidget *topW;
    QWidget *botW;
    QWidget *leftW;
    QWidget *rightW;
    QWidget *midW;


    QPushButton *bookSearchBtn;
    QPushButton *searchBtn;
    QPushButton *appBtn;

    QPushButton *toRecommendBtn;

    QPushButton *myLibraryBtn;
    QPushButton *mainBtn;
    QPushButton *myInfoBtn;
    QPushButton *curBorrowBtn;
    QPushButton *hisBorrowBtn;
    QPushButton *recommendBtn;
    QPushButton *appointBtn;


    //管理员的界面
    QVBoxLayout *adMainLy;
    QHBoxLayout *adTopLy;
    QHBoxLayout *adMidLy;
    QHBoxLayout *adBotLy;
    QVBoxLayout *adLeftLy;
    QVBoxLayout *adRightLy;
    QWidget *adTopW;
    QWidget *adBotW;
    QWidget *adLeftW;
    QWidget *adRightW;
    QWidget *adMidW;

    QPushButton *adBookBtn;
    QPushButton *adBookSearchBtn;
    QPushButton *adBookAddBtn;
    QPushButton *adBookDeleteBtn;
    QPushButton *adBookUpdateBtn;

    QPushButton *adStuBtn;
    QPushButton *adStuSearchBtn;
    QPushButton *adStuAddBtn;
    QPushButton *adStuDeleteBtn;
    QPushButton *adStuUpdateBtn;
    QPushButton *adStuHisBorBtn;
    QPushButton *adStuCurBorBtn;

    QPushButton *adToRecommendBtn;
    QPushButton *adRecUpdateBtn;

    QPushButton *adBorRetBtn;
    QPushButton *adBorBookBtn;
    QPushButton *adRetBookBtn;



public:
     void showAdministrator();
     void showNormalUser();
private slots:
    //普通用户的操作
    void on_bookSearchBtn_clicked();
    void on_searchBtn_clicked();
    void on_appBtn_clicked();

    void on_myLibraryBtn_clicked();
    void on_mainBtn_clicked();
    void on_myInfoBtn_clicked();
    void on_curBorrowBtn_clicked();
    void on_hisBorrowBtn_clicked();
    void on_recommendBtn_clicked();
    void on_toRecommendBtn_clicked();
    void on_appointBtn_clicked();


    //管理员的操作
    void on_adBookBtn_clicked();
    void on_adBookSearchBtn_clicked();
    void on_adBookAddBtn_clicked();
    void on_adBookDeleteBtn_clicked();
    void on_adBookUpdateBtn_clicked();

    void on_adStuBtn_clicked();
    void on_adStuSearchBtn_clicked();
    void on_adStuAddBtn_clicked();
    void on_adStuDeleteBtn_clicked();
    void on_adStuUpdateBtn_clicked();
    void on_adStuHisBorBtn_clicked();
    void on_adStuCurBorBtn_clicked();

    void on_adToRecommendBtn_clicked();
    void on_adRecUpdateBtn_clicked();

    void on_adBorRetBtn_clicked();
    void on_adBorBookBtn_clicked();
    void on_adRetBookBtn_clicked();

};

#endif // MAINWINDOW_H
