#include "mainwindow.h"
#include <QApplication>
#include "commmacro.h"
#ifdef UBUNTU
#include <QWSServer>
#endif
#include <QPalette>
#include <QPixmap>
#include <QFont>
#include <QFontDatabase>
#include <QTextCodec>
#include <QDesktopWidget>
#include <QRect>
#include <QDebug>
#include <QTextCodec>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    qDebug()<<QStyleFactory::keys();
    QApplication::setStyle("Cleanlooks");
//    QApplication::setStyle(QStyleFactory::create( "Plastique"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#ifndef WINDOWS
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));        //支持Tr中文
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //支持中文文件名显示
#endif
    QFont font;
    font.setPointSize(16);
#ifdef UBUNTU
    font.setFamily(("wenquanyi"));
#endif
    font.setBold(false);
    a.setFont(font);
    MainWindow w;
    w.show();

#ifdef UBUNTU
    QWSServer::setCursorVisible(false);     //undisplay cursor
    w.showMaximized();
#endif
    return a.exec();
    /*
    //获取可用桌面大小
    QRect deskRect = QApplication::desktop()->availableGeometry();
    qDebug()<<"availableGeometrywidth="<<deskRect.width()<<"availableGeometryheight="<<deskRect.height();
    //获取主屏幕分辨率
    QRect screenRect = QApplication::desktop()->screenGeometry();
    qDebug()<<"screenGeometrywidth="<<screenRect.width()<<"screenGeometryheight="<<screenRect.height();
    */

}
