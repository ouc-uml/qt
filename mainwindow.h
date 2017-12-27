#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <string>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void newAllButtons();
    void deleteAllButtons();
    void newAllLayouts();
    void deleteAllLayouts();
    void newAllWidgets();
    void deleteAllWidgets();
    void newNorMyLibLW();
    void deleteNorMyLibLW();
    void setThis();
    void addNorTopLy();
    void setNorTopW();
    void addNorLeftMyLibLy();
    void setNorLeftW();
    void addNorRightLy();
    void setNorRightW();
    void addNorBotLy();
    void setNorBotW();
    void addNorMainLy(int flag);
    void connNor();
    void addAdminTopLy();
    void setAdminTopW();
    void addAdminBotLy();
    void setAdminBotW();
    void addAdminMainLy(int flag);
    void connAdmin();
private:
    Ui::MainWindow *ui;

private:
    QLineEdit *BnoLe;
    QLineEdit *EnoLe;
    QLineEdit *userLe;
    QComboBox *zzCb;
    QLineEdit *conditionLe;
    QLineEdit *adconditionLe;
    QTableWidget *table2;
    QTableWidget *table1;
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
    QPushButton *detailBtn;

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
    QPushButton *adBooksAddBtn;

    QPushButton *adStuBtn;
    QPushButton *adStuSearchBtn;
    QPushButton *adStuAddBtn;
    QPushButton *adStuDeleteBtn;
    QPushButton *adStuUpdateBtn;
    QPushButton *adStuHisBorBtn;
    QPushButton *adStuCurBorBtn;
    QPushButton *adStusAddBtn;
    QPushButton *sendMsgBtn;

    QPushButton *adToRecommendBtn;
    QPushButton *adRecUpdateBtn;
    QPushButton *adRecomBtn;

    QPushButton *adBorRetBtn;
    QPushButton *adBorBookBtn;
    QPushButton *adRetBookBtn;

    //root



public:
     void showAdministrator();
     void showNormalUser();
     void recMsg();
     void showEr(string ti,string s);
private slots:

    //普通用户的操作
    void on_bookSearchBtn_clicked();
    void on_searchBtn_clicked();
    void on_detailBtn_clicked();

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
    void on_adBooksAddBtn_clicked();

    void on_adStuBtn_clicked();
    void on_adStuSearchBtn_clicked();
    void on_adStuAddBtn_clicked();
    void on_adStuDeleteBtn_clicked();
    void on_adStuUpdateBtn_clicked();
    void on_adStuHisBorBtn_clicked();
    void on_adStuCurBorBtn_clicked();
    void on_sendMsgBtn_clicked();
    void on_adStusAddBtn_clicked();


    void on_adToRecommendBtn_clicked();
    void on_adRecUpdateBtn_clicked();
    void on_adRecomBtn_clicked();

    void on_adBorRetBtn_clicked();
    void on_adBorBookBtn_clicked();
    void on_adRetBookBtn_clicked();

    //root操作
};

#endif // MAINWINDOW_H
