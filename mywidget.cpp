#include "mywidget.h"
#include <QDebug>
#include "commmacro.h"

extern QMutex m_Mutex;

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{

}

void mywidget::Start_Collect()
{
//    qDebug()<<"####this is mywidget::Start_Collect()###";
//    QMutexLocker locker(&m_Mutex);
    emit start_collect();
}

