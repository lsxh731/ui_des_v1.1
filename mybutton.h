#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);

signals:

public slots:

protected:
    bool event(QEvent* ev);
};

#endif // MYBUTTON_H
