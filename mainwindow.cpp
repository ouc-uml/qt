#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidget>
#include <QWidget>
#include <QSpacerItem>
#include <QLabel>
#include <QTableWidget>
#include <QString>
#include <QStringList>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <QLineEdit>
#include <QComboBox>
#include <QDialog>
#include "torecdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //normal
    bookSearchBtn = new QPushButton("图书检索");
    appBtn = new QPushButton("图书预约");

    toRecommendBtn = new QPushButton("图书荐购");
    myLibraryBtn = new QPushButton("我的图书馆");
    mainBtn      = new QPushButton("主页");
    myInfoBtn    = new QPushButton("我的信息");
    curBorrowBtn = new QPushButton("借阅信息");
    hisBorrowBtn = new QPushButton("历史借阅");
    recommendBtn = new QPushButton("荐购信息");
    appointBtn   = new QPushButton("预约信息");

    //admin
    adBookBtn = new QPushButton("图书管理");
    adBookSearchBtn = new QPushButton("图书搜索");
    adBookAddBtn = new QPushButton("图书增加");
    adBookDeleteBtn = new QPushButton("图书删除");
    adBookUpdateBtn = new QPushButton("图书修改");

    adStuBtn = new QPushButton("学生管理");
    adStuAddBtn = new QPushButton("增加学生");
    adStuDeleteBtn = new QPushButton("删除学生");
    adStuSearchBtn = new QPushButton("学生搜索");
    adStuUpdateBtn = new QPushButton("修改学生");
    adStuHisBorBtn = new QPushButton("历史借阅");
    adStuCurBorBtn = new QPushButton("当前借阅");

    adToRecommendBtn = new QPushButton("荐购管理");
    adRecUpdateBtn = new QPushButton("荐购修改");

    adBorRetBtn = new QPushButton("借还书");
    adBorBookBtn = new QPushButton("借书");
    adRetBookBtn = new QPushButton("还书");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showNormalUser()
{
    this->resize(800,400);
    this->setWindowTitle("图书管理系统");

    mainLayout = new QVBoxLayout;
    toplayout = new QHBoxLayout;
    midlayout = new QHBoxLayout;
    botlayout = new QHBoxLayout;
    leftlayout = new QVBoxLayout;
    rightlayout = new QVBoxLayout;
    topW = new QWidget;
    midW = new QWidget;
    botW = new QWidget;
    leftW = new QWidget;
    rightW = new QWidget;

    //上边导航栏

    toplayout->addWidget(bookSearchBtn);
    toplayout->addWidget(myLibraryBtn);

    topW->setLayout(toplayout);
    topW->setFixedHeight(40);
    mainLayout->addWidget(topW);

    //左边导航栏

    leftlayout->addWidget(mainBtn);
    leftlayout->addWidget(myInfoBtn);
    leftlayout->addWidget(curBorrowBtn);
    leftlayout->addWidget(hisBorrowBtn);
    leftlayout->addWidget(recommendBtn);
    leftlayout->addWidget(appointBtn);

    leftW->setLayout(leftlayout);
    leftW->setFixedWidth(100);
    //leftW->setFixedHeight(150);
    botlayout->addWidget(leftW);


    //右边
    QLabel *caonima  = new QLabel;
    caonima->setText("caoinima");
    rightlayout->addWidget(caonima);

    rightW->setLayout(rightlayout);
    botlayout->addWidget(rightW);
    botW->setLayout(botlayout);

    mainLayout->addWidget(botW);
    ui->centralWidget->setLayout(mainLayout);
    connect(mainBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_mainBtn_clicked()));
    connect(myInfoBtn,      SIGNAL(clicked(bool)),  this,   SLOT(on_myInfoBtn_clicked()));
    connect(curBorrowBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_curBorrowBtn_clicked()));
    connect(hisBorrowBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_hisBorrowBtn_clicked()));
    connect(recommendBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_recommendBtn_clicked()));
    connect(appointBtn,     SIGNAL(clicked(bool)),  this,   SLOT(on_appointBtn_clicked()));
    connect(bookSearchBtn,  SIGNAL(clicked(bool)),  this,   SLOT(on_bookSearchBtn_clicked()));
    connect(myLibraryBtn,  SIGNAL(clicked(bool)),  this,   SLOT(on_myLibraryBtn_clicked()));
}

void MainWindow::on_bookSearchBtn_clicked()
{
    delete mainLayout;
    delete botlayout;
    delete midlayout;
    delete leftlayout;
    delete rightlayout;
    delete midW;
    delete leftW;
    delete rightW;
    delete botW;

    mainLayout = new QVBoxLayout;
    midlayout = new QHBoxLayout;
    botlayout = new QHBoxLayout;
    leftlayout = new QVBoxLayout;
    rightlayout = new QVBoxLayout;
    midW = new QWidget;
    botW = new QWidget;
    leftW = new QWidget;
    rightW = new QWidget;

    //
    //top
    mainLayout->addWidget(topW);
    //mid
    QComboBox *zzCb = new QComboBox;
    QStringList zzCb_sl;
    zzCb_sl<<"按照书名查询"<<"按照书号查询";
    zzCb->addItems(zzCb_sl);
    QLineEdit *conditionLe = new QLineEdit;
    searchBtn = new QPushButton("搜索");
    midlayout->addWidget(zzCb);
    midlayout->addWidget(conditionLe);
    midlayout->addWidget(searchBtn);
    midW->setLayout(midlayout);
    mainLayout->addWidget(midW);
    //left
    appBtn = new QPushButton("图书预约");
    leftlayout->addWidget(appBtn);
    leftW->setLayout(leftlayout);
    botlayout->addWidget(leftW);
    //right
    QTableWidget *table2 = new QTableWidget;
    table2->setColumnCount(6);
    QStringList tableheader;
    tableheader<<"图书号码"<<"书名"<<"作者"<<"馆藏地"<<"借阅状态"<<"备注";
    table2->setHorizontalHeaderLabels(tableheader);
    table2->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table2->resizeColumnsToContents();
    table2->resizeRowsToContents();
    rightlayout->addWidget(table2);
    rightW->setLayout(rightlayout);
    botlayout->addWidget(rightW);

    //

    botW->setLayout(botlayout);
    mainLayout->addWidget(botW);
    ui->centralWidget->setLayout(mainLayout);

    connect(bookSearchBtn,  SIGNAL(clicked(bool)),  this,   SLOT(on_bookSearchBtn_clicked()));
    connect(myLibraryBtn,  SIGNAL(clicked(bool)),  this,   SLOT(on_myLibraryBtn_clicked()));
    connect(searchBtn,  SIGNAL(clicked(bool)),  this,   SLOT(on_searchBtn_clicked()));
    connect(appBtn,  SIGNAL(clicked(bool)),  this,   SLOT(on_appBtn_clicked()));

}

void MainWindow::on_searchBtn_clicked()
{

}

void MainWindow::on_appBtn_clicked()
{

}

void MainWindow::on_myLibraryBtn_clicked()
{
    delete mainLayout;
    delete botlayout;
    delete midlayout;
    delete leftlayout;
    delete rightlayout;
    delete midW;
    delete leftW;
    delete rightW;
    delete botW;

    mainLayout = new QVBoxLayout;
    midlayout = new QHBoxLayout;
    botlayout = new QHBoxLayout;
    leftlayout = new QVBoxLayout;
    rightlayout = new QVBoxLayout;
    midW = new QWidget;
    botW = new QWidget;
    leftW = new QWidget;
    rightW = new QWidget;


    //上边导航栏

    mainLayout->addWidget(topW);

    //左边导航栏
    mainBtn      = new QPushButton("主页");
    leftlayout->addWidget(mainBtn);
    myInfoBtn    = new QPushButton("我的信息");
    leftlayout->addWidget(myInfoBtn);
    curBorrowBtn = new QPushButton("借阅信息");
    leftlayout->addWidget(curBorrowBtn);
    hisBorrowBtn = new QPushButton("历史借阅");
    leftlayout->addWidget(hisBorrowBtn);
    recommendBtn = new QPushButton("荐购信息");
    leftlayout->addWidget(recommendBtn);
    appointBtn   = new QPushButton("预约信息");
    leftlayout->addWidget(appointBtn);

    leftW->setLayout(leftlayout);
    leftW->setFixedWidth(100);
    //leftW->setFixedHeight(150);
    botlayout->addWidget(leftW);


    //右边
    QLabel *caonima  = new QLabel;
    caonima->setText("caoinima");
    rightlayout->addWidget(caonima);

    rightW->setLayout(rightlayout);
    botlayout->addWidget(rightW);
    botW->setLayout(botlayout);

    mainLayout->addWidget(botW);
    ui->centralWidget->setLayout(mainLayout);

    connect(mainBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_mainBtn_clicked()));
    connect(myInfoBtn,      SIGNAL(clicked(bool)),  this,   SLOT(on_myInfoBtn_clicked()));
    connect(curBorrowBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_curBorrowBtn_clicked()));
    connect(hisBorrowBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_hisBorrowBtn_clicked()));
    connect(recommendBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_recommendBtn_clicked()));
    connect(appointBtn,     SIGNAL(clicked(bool)),  this,   SLOT(on_appointBtn_clicked()));
    connect(bookSearchBtn,  SIGNAL(clicked(bool)),  this,   SLOT(on_bookSearchBtn_clicked()));
    connect(myLibraryBtn,  SIGNAL(clicked(bool)),  this,   SLOT(on_myLibraryBtn_clicked()));
}

void MainWindow::on_mainBtn_clicked()
{
    delete rightlayout;
    delete botlayout;
    delete mainLayout;
    delete rightW;

    mainLayout = new QVBoxLayout;
    botlayout = new QHBoxLayout;
    rightlayout = new QVBoxLayout;
    rightW = new QWidget;

    //
    QLabel *caonima  = new QLabel;
    caonima->setText("aaaaaaaaaaaaaaaaaaaaa");
    rightlayout->addWidget(caonima);
    //


    rightW->setLayout(rightlayout);
    botlayout->addWidget(leftW);
    botlayout->addWidget(rightW);
    botW->setLayout(botlayout);
    mainLayout->addWidget(topW);
    mainLayout->addWidget(botW);

    ui->centralWidget->setLayout(mainLayout);
}

void MainWindow::on_myInfoBtn_clicked()
{
    delete rightlayout;
    delete botlayout;
    delete mainLayout;
    delete rightW;

    mainLayout = new QVBoxLayout;
    botlayout = new QHBoxLayout;
    rightlayout = new QVBoxLayout;
    rightW = new QWidget;

    QLabel *name = new QLabel;
    name->setText("姓名:zz");
    rightlayout->addWidget(name);

    QLabel *maxBroNum = new QLabel;
    maxBroNum->setText("最大可借图书:12");
    rightlayout->addWidget(maxBroNum);

    QLabel *userType = new QLabel;
    userType->setText("用户类型:普通用户");
    rightlayout->addWidget(userType);

    QLabel *maxAppNum = new QLabel;
    maxAppNum->setText("最大可预约数量:3");
    rightlayout->addWidget(maxAppNum);

    rightW->setLayout(rightlayout);
    botlayout->addWidget(leftW);
    botlayout->addWidget(rightW);
    botW->setLayout(botlayout);
    mainLayout->addWidget(topW);
    mainLayout->addWidget(botW);

    ui->centralWidget->setLayout(mainLayout);
}

void MainWindow::on_curBorrowBtn_clicked()
{
    delete rightlayout;
    delete botlayout;
    delete mainLayout;
    delete rightW;

    mainLayout = new QVBoxLayout;
    botlayout = new QHBoxLayout;
    rightlayout = new QVBoxLayout;
    rightW = new QWidget;
    //
    QTableWidget *table1 = new QTableWidget;
    table1->setColumnCount(6);

    QStringList tableheader;
    tableheader<<"图书号码"<<"书名"<<"作者"<<"借阅日期"<<"应还日期"<<"馆藏地"<<"备注";
    table1->setHorizontalHeaderLabels(tableheader);
    table1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    table1->resizeColumnsToContents();
    table1->resizeRowsToContents();

    rightlayout->addWidget(table1);
    //
    rightW->setLayout(rightlayout);
    botlayout->addWidget(leftW);
    botlayout->addWidget(rightW);
    botW->setLayout(botlayout);
    mainLayout->addWidget(topW);
    mainLayout->addWidget(botW);

    ui->centralWidget->setLayout(mainLayout);
}

void MainWindow::on_hisBorrowBtn_clicked()
{
    delete rightlayout;
    delete botlayout;
    delete mainLayout;
    delete rightW;

    mainLayout = new QVBoxLayout;
    botlayout = new QHBoxLayout;
    rightlayout = new QVBoxLayout;
    rightW = new QWidget;
    //
    QTableWidget *table1 = new QTableWidget;
    table1->setColumnCount(6);

    QStringList tableheader;
    tableheader<<"图书号码"<<"书名"<<"作者"<<"借阅日期"<<"应还日期"<<"馆藏地"<<"备注";
    table1->setHorizontalHeaderLabels(tableheader);
    table1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    table1->resizeColumnsToContents();
    table1->resizeRowsToContents();

    rightlayout->addWidget(table1);
    //
    rightW->setLayout(rightlayout);
    botlayout->addWidget(leftW);
    botlayout->addWidget(rightW);
    botW->setLayout(botlayout);
    mainLayout->addWidget(topW);
    mainLayout->addWidget(botW);

    ui->centralWidget->setLayout(mainLayout);
}

void MainWindow::on_recommendBtn_clicked()
{
    delete rightlayout;
    delete botlayout;
    delete mainLayout;
    delete rightW;

    mainLayout = new QVBoxLayout;
    botlayout = new QHBoxLayout;
    rightlayout = new QVBoxLayout;
    rightW = new QWidget;

    //
    QTableWidget *table1 = new QTableWidget;
    table1->setColumnCount(6);

    QStringList tableheader;
    tableheader<<"编号"<<"书名"<<"责任者"<<"出版信息"<<"荐购日期"<<"荐购状态"<<"备注";
    table1->setHorizontalHeaderLabels(tableheader);
    table1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    table1->resizeColumnsToContents();
    table1->resizeRowsToContents();

    rightlayout->addWidget(table1);
    toRecommendBtn = new QPushButton("图书荐购");
    rightlayout->addWidget(toRecommendBtn);
    //

    rightW->setLayout(rightlayout);
    botlayout->addWidget(leftW);
    botlayout->addWidget(rightW);
    botW->setLayout(botlayout);
    mainLayout->addWidget(topW);
    mainLayout->addWidget(botW);

    ui->centralWidget->setLayout(mainLayout);
    connect(toRecommendBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_toRecommendBtn_clicked()));
}

void MainWindow::on_toRecommendBtn_clicked()
{
    toRecDialog toRecDlg;
    toRecDlg.exec();
}

void MainWindow::on_appointBtn_clicked()
{
    delete rightlayout;
    delete botlayout;
    delete mainLayout;
    delete rightW;

    mainLayout = new QVBoxLayout;
    botlayout = new QHBoxLayout;
    rightlayout = new QVBoxLayout;
    rightW = new QWidget;
    //
    QTableWidget *table1 = new QTableWidget;
    table1->setColumnCount(9);

    QStringList tableheader;
    tableheader<<"图书号码"<<"书名"<<"作者"<<"馆藏地"<<"到书日"<<"截止日期"<<"取书地"<<"状态"<<"附注";
    table1->setHorizontalHeaderLabels(tableheader);
    table1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    table1->resizeColumnsToContents();
    table1->resizeRowsToContents();

    rightlayout->addWidget(table1);
    //
    rightW->setLayout(rightlayout);
    botlayout->addWidget(leftW);
    botlayout->addWidget(rightW);
    botW->setLayout(botlayout);
    mainLayout->addWidget(topW);
    mainLayout->addWidget(botW);

    ui->centralWidget->setLayout(mainLayout);
}

//管理员的操作
void MainWindow::showAdministrator()
{
    this->resize(800,400);
    this->setWindowTitle("图书管理系统");

    adMainLy = new QVBoxLayout;
    adTopLy = new QHBoxLayout;
    adMidLy = new QHBoxLayout;
    adBotLy = new QHBoxLayout;
    adLeftLy = new QVBoxLayout;
    adRightLy = new QVBoxLayout;
    adTopW = new QWidget;
    adMidW = new QWidget;
    adBotW = new QWidget;
    adLeftW = new QWidget;
    adRightW = new QWidget;

    //上边导航栏

    adTopLy->addWidget(adBookBtn);
    adTopLy->addWidget(adStuBtn);
    adTopLy->addWidget(adToRecommendBtn);
    adTopLy->addWidget(adBorRetBtn);

    adTopW->setLayout(adTopLy);
    adTopW->setFixedHeight(40);
    adMainLy->addWidget(adTopW);

    //中间
    QComboBox *zzCb = new QComboBox;
    QStringList zzCb_sl;
    zzCb_sl<<"按照书名查询"<<"按照书号查询";
    zzCb->addItems(zzCb_sl);
    QLineEdit *adconditionLe = new QLineEdit;
    adMidLy->addWidget(zzCb);
    adMidLy->addWidget(adconditionLe);
    adMidLy->addWidget(adBookSearchBtn);
    adMidW->setLayout(adMidLy);
    adMainLy->addWidget(adMidW);

    //左边导航栏

    adLeftLy->addWidget(adBookAddBtn);
    adLeftLy->addWidget(adBookDeleteBtn);
    adLeftLy->addWidget(adBookUpdateBtn);

    adLeftW->setLayout(adLeftLy);
    adLeftW->setFixedWidth(100);
    //leftW->setFixedHeight(150);
    adBotLy->addWidget(adLeftW);


    //右边
    QTableWidget *table1 = new QTableWidget;
    table1->setColumnCount(5);
    QStringList tableheader;
    tableheader<<"编号"<<"书名"<<"责任者"<<"出版信息"<<"备注";
    table1->setHorizontalHeaderLabels(tableheader);
    table1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table1->resizeColumnsToContents();
    table1->resizeRowsToContents();

    adRightLy->addWidget(table1);
    adRightW->setLayout(adRightLy);
    adBotLy->addWidget(adRightW);
    adBotW->setLayout(adBotLy);
    adMainLy->addWidget(adBotW);

    ui->centralWidget->setLayout(adMainLy);
    connect(adBookBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_adBookBtn_clicked()));
    connect(adBookAddBtn,      SIGNAL(clicked(bool)),  this,   SLOT(on_adBookAddBtn_clicked()));
    connect(adBookDeleteBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBookDeleteBtn_clicked()));
    connect(adBookUpdateBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBookUpdateBtn_clicked()));
    connect(adBookSearchBtn,     SIGNAL(clicked(bool)),  this,   SLOT(on_adBookSearchBtn_clicked()));
    connect(adStuBtn,     SIGNAL(clicked(bool)),  this,   SLOT(on_adStuBtn_clicked()));
    connect(adToRecommendBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adToRecommendBtn_clicked()));
    connect(adBorRetBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBorRetBtn_clicked()));
}

void MainWindow::on_adBookBtn_clicked()
{

    delete adMainLy;
    delete adTopLy;
    delete adMidLy;
    delete adBotLy;
    delete adLeftLy;
    delete adRightLy;

    delete adLeftW;
    delete adRightW;
    delete adTopW;
    delete adMidW;
    delete adBotW;


    adMainLy = new QVBoxLayout;
    adTopLy = new QHBoxLayout;
    adMidLy = new QHBoxLayout;
    adBotLy = new QHBoxLayout;
    adLeftLy = new QVBoxLayout;
    adRightLy = new QVBoxLayout;
    adTopW = new QWidget;
    adMidW = new QWidget;
    adBotW = new QWidget;
    adLeftW = new QWidget;
    adRightW = new QWidget;
    adBookBtn = new QPushButton("图书管理");
    adBookSearchBtn = new QPushButton("图书搜索");
    adBookAddBtn = new QPushButton("图书增加");
    adBookDeleteBtn = new QPushButton("图书删除");
    adBookUpdateBtn = new QPushButton("图书修改");

    adStuBtn = new QPushButton("学生管理");

    adToRecommendBtn = new QPushButton("荐购管理");

    adBorRetBtn = new QPushButton("借还书");

    //上边导航栏

    adTopLy->addWidget(adBookBtn);
    adTopLy->addWidget(adStuBtn);
    adTopLy->addWidget(adToRecommendBtn);
    adTopLy->addWidget(adBorRetBtn);

    adTopW->setLayout(adTopLy);
    adTopW->setFixedHeight(40);
    adMainLy->addWidget(adTopW);

    //中间
    QComboBox *zzCb = new QComboBox;
    QStringList zzCb_sl;
    zzCb_sl<<"按照书名查询"<<"按照书号查询";
    zzCb->addItems(zzCb_sl);
    QLineEdit *adconditionLe = new QLineEdit;
    adMidLy->addWidget(zzCb);
    adMidLy->addWidget(adconditionLe);
    adMidLy->addWidget(adBookSearchBtn);
    adMidW->setLayout(adMidLy);
    adMainLy->addWidget(adMidW);

    //左边导航栏

    adLeftLy->addWidget(adBookAddBtn);
    adLeftLy->addWidget(adBookDeleteBtn);
    adLeftLy->addWidget(adBookUpdateBtn);

    adLeftW->setLayout(adLeftLy);
    adLeftW->setFixedWidth(100);
    //leftW->setFixedHeight(150);
    adBotLy->addWidget(adLeftW);


    //右边
    QTableWidget *table1 = new QTableWidget;
    table1->setColumnCount(5);
    QStringList tableheader;
    tableheader<<"编号"<<"书名"<<"责任者"<<"出版信息"<<"备注";
    table1->setHorizontalHeaderLabels(tableheader);
    table1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table1->resizeColumnsToContents();
    table1->resizeRowsToContents();

    adRightLy->addWidget(table1);
    adRightW->setLayout(adRightLy);
    adBotLy->addWidget(adRightW);
    adBotW->setLayout(adBotLy);
    adMainLy->addWidget(adBotW);

    ui->centralWidget->setLayout(adMainLy);
    connect(adBookBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_adBookBtn_clicked()));
    connect(adBookAddBtn,      SIGNAL(clicked(bool)),  this,   SLOT(on_adBookAddBtn_clicked()));
    connect(adBookDeleteBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBookDeleteBtn_clicked()));
    connect(adBookUpdateBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBookUpdateBtn_clicked()));
    connect(adBookSearchBtn,     SIGNAL(clicked(bool)),  this,   SLOT(on_adBookSearchBtn_clicked()));
    connect(adStuBtn,     SIGNAL(clicked(bool)),  this,   SLOT(on_adStuBtn_clicked()));
    connect(adToRecommendBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adToRecommendBtn_clicked()));
    connect(adBorRetBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBorRetBtn_clicked()));

}

void MainWindow::on_adBookSearchBtn_clicked()
{

}

void MainWindow::on_adBookAddBtn_clicked()
{

}

void MainWindow::on_adBookDeleteBtn_clicked()
{

}

void MainWindow::on_adBookUpdateBtn_clicked()
{

}

void MainWindow::on_adStuBtn_clicked()
{

    delete adMainLy;
    delete adTopLy;
    delete adMidLy;
    delete adBotLy;
    delete adLeftLy;
    delete adRightLy;

    delete adLeftW;
    delete adRightW;
    delete adTopW;
    delete adMidW;
    delete adBotW;


    adMainLy = new QVBoxLayout;
    adTopLy = new QHBoxLayout;
    adMidLy = new QHBoxLayout;
    adBotLy = new QHBoxLayout;
    adLeftLy = new QVBoxLayout;
    adRightLy = new QVBoxLayout;
    adTopW = new QWidget;
    adMidW = new QWidget;
    adBotW = new QWidget;
    adLeftW = new QWidget;
    adRightW = new QWidget;


    adBookBtn = new QPushButton("图书管理");

    adStuBtn = new QPushButton("学生管理");
    adStuAddBtn = new QPushButton("增加学生");
    adStuDeleteBtn = new QPushButton("删除学生");
    adStuSearchBtn = new QPushButton("学生搜索");
    adStuUpdateBtn = new QPushButton("修改学生");
    adStuHisBorBtn = new QPushButton("历史借阅");
    adStuCurBorBtn = new QPushButton("当前借阅");

    adToRecommendBtn = new QPushButton("荐购管理");

    adBorRetBtn = new QPushButton("借还书");
    //上边导航栏
    adTopLy->addWidget(adBookBtn);
    adTopLy->addWidget(adStuBtn);
    adTopLy->addWidget(adToRecommendBtn);
    adTopLy->addWidget(adBorRetBtn);
    adTopW->setLayout(adTopLy);
    adTopW->setFixedHeight(40);
    adMainLy->addWidget(adTopW);

    //中间
    QLabel *zzLb = new QLabel;
    zzLb->setText("查询学号");
    QLineEdit *adconditionLe = new QLineEdit;
    adMidLy->addWidget(zzLb);
    adMidLy->addWidget(adconditionLe);
    adMidLy->addWidget(adStuSearchBtn);
    adMidW->setLayout(adMidLy);
    adMainLy->addWidget(adMidW);

    //左边导航栏

    adLeftLy->addWidget(adStuAddBtn);
    adLeftLy->addWidget(adStuDeleteBtn);
    adLeftLy->addWidget(adStuUpdateBtn);
    adLeftLy->addWidget(adStuHisBorBtn);
    adLeftLy->addWidget(adStuCurBorBtn);

    adLeftW->setLayout(adLeftLy);
    adLeftW->setFixedWidth(100);
    //leftW->setFixedHeight(150);
    adBotLy->addWidget(adLeftW);


    //右边
    QTableWidget *table1 = new QTableWidget;
    table1->setColumnCount(5);
    QStringList tableheader;
    tableheader<<"学号"<<"姓名"<<"年级"<<"专业"<<"备注";
    table1->setHorizontalHeaderLabels(tableheader);
    table1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table1->resizeColumnsToContents();
    table1->resizeRowsToContents();

    adRightLy->addWidget(table1);
    adRightW->setLayout(adRightLy);
    adBotLy->addWidget(adRightW);
    adBotW->setLayout(adBotLy);
    adMainLy->addWidget(adBotW);

    ui->centralWidget->setLayout(adMainLy);
    connect(adBookBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_adBookBtn_clicked()));
    connect(adStuBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_adStuBtn_clicked()));
    connect(adStuAddBtn,      SIGNAL(clicked(bool)),  this,   SLOT(on_adStuAddBtn_clicked()));
    connect(adStuDeleteBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adStuDeleteBtn_clicked()));
    connect(adStuUpdateBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adStuUpdateBtn_clicked()));
    connect(adStuSearchBtn,     SIGNAL(clicked(bool)),  this,   SLOT(on_adStuSearchBtn_clicked()));
    connect(adToRecommendBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adToRecommendBtn_clicked()));
    connect(adBorRetBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBorRetBtn_clicked()));
}

void MainWindow::on_adStuSearchBtn_clicked()
{

}

void MainWindow::on_adStuAddBtn_clicked()
{

}

void MainWindow::on_adStuDeleteBtn_clicked()
{

}

void MainWindow::on_adStuUpdateBtn_clicked()
{

}

void MainWindow::on_adStuHisBorBtn_clicked()
{

}

void MainWindow::on_adStuCurBorBtn_clicked()
{

}

void MainWindow::on_adToRecommendBtn_clicked()
{

    delete adMainLy;
    delete adTopLy;
    delete adMidLy;
    delete adBotLy;
    delete adLeftLy;
    delete adRightLy;

    delete adLeftW;
    delete adRightW;
    delete adTopW;
    delete adMidW;
    delete adBotW;


    adMainLy = new QVBoxLayout;
    adTopLy = new QHBoxLayout;
    adMidLy = new QHBoxLayout;
    adBotLy = new QHBoxLayout;
    adLeftLy = new QVBoxLayout;
    adRightLy = new QVBoxLayout;
    adTopW = new QWidget;
    adMidW = new QWidget;
    adBotW = new QWidget;
    adLeftW = new QWidget;
    adRightW = new QWidget;

    adBookBtn = new QPushButton("图书管理");

    adStuBtn = new QPushButton("学生管理");

    adToRecommendBtn = new QPushButton("荐购管理");
    adRecUpdateBtn = new QPushButton("荐购修改");
    adBorRetBtn = new QPushButton("借还书");
    //上边导航栏
    adTopLy->addWidget(adBookBtn);
    adTopLy->addWidget(adStuBtn);
    adTopLy->addWidget(adToRecommendBtn);
    adTopLy->addWidget(adBorRetBtn);
    adTopW->setLayout(adTopLy);
    adMainLy->addWidget(adTopW);


    //左边导航栏

    adLeftLy->addWidget(adRecUpdateBtn);

    adLeftW->setLayout(adLeftLy);
    adLeftW->setFixedWidth(100);
    //leftW->setFixedHeight(150);
    adBotLy->addWidget(adLeftW);


    //右边
    QTableWidget *table1 = new QTableWidget;
    table1->setColumnCount(5);
    QStringList tableheader;
    tableheader<<"编号"<<"书名"<<"作者"<<"出版社"<<"备注";
    table1->setHorizontalHeaderLabels(tableheader);
    table1->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table1->resizeColumnsToContents();
    table1->resizeRowsToContents();

    adRightLy->addWidget(table1);
    adRightW->setLayout(adRightLy);
    adBotLy->addWidget(adRightW);
    adBotW->setLayout(adBotLy);
    adMainLy->addWidget(adBotW);

    ui->centralWidget->setLayout(adMainLy);
    connect(adBookBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_adBookBtn_clicked()));
    connect(adStuBtn,     SIGNAL(clicked(bool)),  this,   SLOT(on_adStuBtn_clicked()));
    connect(adToRecommendBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adToRecommendBtn_clicked()));
    connect(adRecUpdateBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_adRecUpdateBtn_clicked()));
    connect(adBorRetBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBorRetBtn_clicked()));
}

void MainWindow::on_adRecUpdateBtn_clicked()
{

}

void MainWindow::on_adBorRetBtn_clicked()
 {
     delete adMainLy;
     delete adTopLy;
     delete adMidLy;
     delete adBotLy;
     delete adLeftLy;
     delete adRightLy;

     delete adLeftW;
     delete adRightW;
     delete adTopW;
     delete adMidW;
     delete adBotW;


     adMainLy = new QVBoxLayout;
     adTopLy = new QHBoxLayout;
     adMidLy = new QHBoxLayout;
     adBotLy = new QHBoxLayout;
     adLeftLy = new QVBoxLayout;
     adRightLy = new QVBoxLayout;
     adTopW = new QWidget;
     adMidW = new QWidget;
     adBotW = new QWidget;
     adLeftW = new QWidget;
     adRightW = new QWidget;

     adBookBtn = new QPushButton("图书管理");

     adStuBtn = new QPushButton("学生管理");

     adToRecommendBtn = new QPushButton("荐购管理");

     adBorRetBtn = new QPushButton("借还书");
     adBorBookBtn = new QPushButton("借书");
     adRetBookBtn = new QPushButton("还书");
     //上边导航栏
     adTopLy->addWidget(adBookBtn);
     adTopLy->addWidget(adStuBtn);
     adTopLy->addWidget(adToRecommendBtn);
     adTopLy->addWidget(adBorRetBtn);
     adTopW->setLayout(adTopLy);
     adTopW->setFixedHeight(40);
     adMainLy->addWidget(adTopW);


     //左边导航栏

     adLeftLy->addWidget(adBorBookBtn);
     adLeftLy->addWidget(adRetBookBtn);

     adLeftW->setLayout(adLeftLy);
     adLeftW->setFixedWidth(100);
     //leftW->setFixedHeight(150);
     adBotLy->addWidget(adLeftW);


     //右边
     QLabel *BnoLb = new QLabel("ISBN号码");
     QLabel *EnoLb = new QLabel("书号");
     QLabel *userLb = new QLabel("学号");
     QLineEdit *BnoLe = new QLineEdit;
     QLineEdit *EnoLe = new QLineEdit;
     QLineEdit *userLe = new QLineEdit;
     QGridLayout *tmpAdRightLy = new QGridLayout;

     tmpAdRightLy->addWidget(BnoLb,1,0,1,1);
     tmpAdRightLy->addWidget(BnoLe,1,1,1,2);
     tmpAdRightLy->addWidget(EnoLb,2,0,2,1);
     tmpAdRightLy->addWidget(EnoLe,2,1,2,2);
     tmpAdRightLy->addWidget(userLb,3,0,3,1);
     tmpAdRightLy->addWidget(userLe,3,1,3,2);

     adRightW->setLayout(tmpAdRightLy);
     adRightW->setFixedSize(300,120);
     adBotLy->addWidget(adRightW);
     adBotW->setLayout(adBotLy);
     adMainLy->addWidget(adBotW);

     ui->centralWidget->setLayout(adMainLy);
     connect(adBookBtn,        SIGNAL(clicked(bool)),  this,   SLOT(on_adBookBtn_clicked()));
     connect(adStuBtn,     SIGNAL(clicked(bool)),  this,   SLOT(on_adStuBtn_clicked()));
     connect(adToRecommendBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adToRecommendBtn_clicked()));
     connect(adBorRetBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBorRetBtn_clicked()));
     connect(adBorBookBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adBorBookBtn_clicked()));
     connect(adRetBookBtn,   SIGNAL(clicked(bool)),  this,   SLOT(on_adRetBookBtn_clicked()));
 }

void MainWindow::on_adBorBookBtn_clicked()
 {

 }

void MainWindow::on_adRetBookBtn_clicked()
 {

 }
