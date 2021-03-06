#-------------------------------------------------
#
# Project created by QtCreator 2017-11-14T21:22:04
#
#-------------------------------------------------

QT       += core gui

LIBS += -lpthread libwsock32 libws2_32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = books
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    logindialog.cpp \
    global.cpp \
    torecdialog.cpp \
    errordialog.cpp \
    confirmdialog.cpp \
    addbookdialog.cpp \
    addstudialog.cpp \
    stubordialog.cpp \
    md5.cpp \
    changepwddialog.cpp \
    clients.cpp \
    library.cpp \
    deletebookdialog.cpp \
    sendmsgdialog.cpp

HEADERS += \
        mainwindow.h \
    logindialog.h \
    global.h \
    torecdialog.h \
    errordialog.h \
    confirmdialog.h \
    addbookdialog.h \
    addstudialog.h \
    stubordialog.h \
    connect.h \
    library.h \
    md5.h \
    changepwddialog.h \
    deletebookdialog.h \
    sendmsgdialog.h

FORMS += \
        mainwindow.ui \
    logindialog.ui \
    torecdialog.ui \
    errordialog.ui \
    confirmdialog.ui \
    addbookdialog.ui \
    addstudialog.ui \
    stubordialog.ui \
    changepwddialog.ui \
    deletebookdialog.ui \
    sendmsgdialog.ui
