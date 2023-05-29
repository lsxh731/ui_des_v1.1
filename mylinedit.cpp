#include "mylinedit.h"
#include <QDebug>

mylinedit::mylinedit(QWidget *parent) :
    QLineEdit(parent)
{

}

void mylinedit::mousePressEvent(QMouseEvent *)
{
    emit mylineedit_clicked();
}
