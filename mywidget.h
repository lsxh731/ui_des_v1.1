#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMutex>
#include <QMutexLocker>

class mywidget : public QWidget
{
    Q_OBJECT
public:
    explicit mywidget(QWidget *parent = 0);
    void Start_Collect();


signals:
    void start_collect();

public slots:
};

#endif // MYWIDGET_H
