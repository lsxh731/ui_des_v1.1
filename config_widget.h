#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <QDialog>
#include "keyboarddlg.h"
#include "mylinedit.h"
#include <QMutex>
#include <QMutexLocker>
#include "commmacro.h"
#include <QTimer>
#include <unistd.h>
#include <QMessageBox>
#include "mesdialog.h"

namespace Ui {
class config_widget;

}

class config_widget : public QDialog
{
    Q_OBJECT

public:
    explicit config_widget(QWidget *parent = 0);
    ~config_widget();

    CKeyBoardDlg *keyboard;
    Mesdialog *MesDialog;
    Mesdialog *MesDialog2;

    bool bt_change_language;  //false:chinese,true:english

    bool which_keyboard; //true:pre_position,false:control_frequeny

    bool con_w_open;       //true:open   false:close

    double posi;
    double pres;
    QString str_posi;
    QString str_pres;
    float target;
    int fd_buzzer;
    double Zero_p;
    QString str_zero;

    QTimer *QTimerBuzzer;

    rdButton rdb;



public slots:
    void ReDisplayScreen();
    void BuzzerOpen();
    void BuzzerClose();
    void QTimerBuzzermsdell();

private slots:
    void button_home_pressed();
    void button_home_released();
    void button_logsave_pressed();
    void button_logsave_released();

    void P_show_keyboard();
    void F_show_keyboard();

    void Get_keyboard_value();

    void change_brightness(int value);


    void on_pb_zylight_pressed();

signals:
    void configWidgetClose();
    void stopManuPWM();
    void startManuPWM();
    void ChangeTarget();

private:
    Ui::config_widget *ui;

public:
    void ToShowChinese();
    void ToShowEnglish();

};


#endif // CONFIG_WIDGET_H
