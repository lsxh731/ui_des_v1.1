#-------------------------------------------------
#
# Project created by QtCreator 2021-01-12T19:40:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ui_des
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    config_widget.cpp \
    keyboarddlg.cpp \
    mylinedit.cpp \
    mywidget.cpp \
    valve.cpp \
    mypid.cpp \
    mybutton.cpp \
    myi2c.cpp \
    mesdialog.cpp \
    pwmqthread.cpp

HEADERS  += mainwindow.h \
    config_widget.h \
    keyboarddlg.h \
    mylinedit.h \
    spi.h \
    mywidget.h \
    commmacro.h \
    valve.h \
    mypid.h \
    mybutton.h \
    myi2c.h \
    mesdialog.h \
    pwmqthread.h

FORMS    += mainwindow.ui \
    config_widget.ui \
    keyboard.ui \
    mesdialog.ui

RESOURCES += \
    image.qrc


DISTFILES += \
    png/bt_off.png \
    png/bt_on.png
CONFIG += C++11
