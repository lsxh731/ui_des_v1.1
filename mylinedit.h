#ifndef MYLINEDIT_H
#define MYLINEDIT_H

#include <QLineEdit>
#include <QMouseEvent>
#include <QEvent>

class mylinedit : public QLineEdit
{
    Q_OBJECT
public:
    explicit mylinedit(QWidget *parent = 0);


signals:
    void mylineedit_clicked(void);

public slots:

protected:
    void mousePressEvent(QMouseEvent *);
private:



};

#endif // MYLINEDIT_H
