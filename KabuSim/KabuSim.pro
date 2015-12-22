#-------------------------------------------------
#
# Project created by QtCreator 2015-12-10T14:59:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KabuSim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    boardtablewidget.cpp \
    graphdrawwidget.cpp

HEADERS  += mainwindow.h \
    boardtablewidget.h \
    graphdrawwidget.h

FORMS    += mainwindow.ui
