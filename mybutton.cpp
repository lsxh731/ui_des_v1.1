#include "mybutton.h"
#include <QTouchEvent>
#include <QDebug>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{
    this->setAttribute(Qt::WA_AcceptTouchEvents);

}

bool MyButton::event(QEvent *ev)
{
    switch (ev->type())
    {
    case QEvent::Enter:
    {
        qDebug()<<"QEvent::Enter:";
        ev->accept();
        return true;
    }
    case QEvent::TouchUpdate:
    {
        qDebug()<<"QEvent::TouchUpdate:";
        ev->accept();
        return true;
    }
    }

//    if(ev->type() == QEvent::TouchBegin)
//    {
//        qDebug()<<"screen touch QEvent::TouchBegin!!!";
//        QTouchEvent * touch = static_cast<QTouchEvent*>(ev);
//        if(touch->touchPointStates()&Qt::TouchPointPressed)
//            qDebug()<<"screen touch point pressed!!!";
//        else if(touch->touchPointStates()&Qt::TouchPointReleased)
//            qDebug()<<"screen touch point released!!!";
//    }
    return QWidget::event(ev);
}
