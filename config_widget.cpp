#include "config_widget.h"
#include "ui_config_widget.h"
#include <QFont>
#include <QDebug>
#include <QProcess>
#include <QSlider>
#include <QFile>

int ifq;
extern USEPOSI Useposi;
extern SETPOSI Setpposi;

QMutex m_Mutex;

config_widget::config_widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config_widget)
{
    ui->setupUi(this);
    keyboard = new CKeyBoardDlg();
    MesDialog = new Mesdialog();
    MesDialog2 = new Mesdialog();
    this->setModal(true);
    QFont ft;
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->frame->setObjectName("mysubframe");
    ui->frame->setStyleSheet("QFrame#mysubframe{border-image:url(:/png/config_uinew.jpg)}" );

    ui->Button_Home->setStyleSheet("border-radius:8px;border-image:url(:/png/homedefault.png)");
    ft.setPointSize(16);
    ft.setWeight(75);
    ui->lab_home->setFont(ft);
    ui->lab_home->setText("Home");
    ui->lab_home->setStyleSheet("color:#FFFFFF;");
    ui->lab_home->setAlignment(Qt::AlignLeft);
    connect(ui->Button_Home,SIGNAL(pressed()),this,SLOT(button_home_pressed()));
    connect(ui->Button_Home,SIGNAL(released()),this,SLOT(button_home_released()));

    ft.setPointSize(36);
    ft.setWeight(75);
    ui->lab_title_man->setFont(ft);
    ui->lab_title_man->setStyleSheet("color:#FFFFFF;");
    ui->lab_title_man->setAlignment(Qt::AlignCenter);
    ui->lab_title_man->setText("振 动 台 数 字 自 动 对 中 系 统"); //Digital Automatic Alignment System of Plain Jolter

    ft.setPointSize(24);
    ui->lab_title_posi->setFont(ft);
    ui->lab_title_posi->setStyleSheet("border-radius:5px;color:#FFFFFF;background:rgb(38,104,157);");
    ui->lab_title_posi->setAlignment(Qt::AlignCenter);
    ui->lab_title_posi->setText("绝 对 位 置"); //DuiZhong Position

    ft.setPointSize(16);
    ui->lab_absp_txt->setFont(ft);
    ui->lab_absp_txt->setStyleSheet("color:#FFFFFF;");
    ui->lab_absp_txt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->lab_absp_txt->setText("Abs position");
    ui->lab_absp_mm->setFont(ft);
    ui->lab_absp_mm->setStyleSheet("color:#FFFFFF;");
    ui->lab_absp_mm->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->lab_absp_mm->setText("mm");

    ft.setPointSize(24);
    ui->lcdNum_absp->setFont(ft);
    ui->lcdNum_absp->setStyleSheet("border-radius:5px;font-size:90px;color:#000000;background:#FFFFFF;border-image:url(:/png/lcd_back.png)");
    ui->lcdNum_absp->setDigitCount(6);
    ui->lcdNum_absp->display(0.88);

    ft.setPointSize(16);
    ui->lab_pres_txt->setFont(ft);
    ui->lab_pres_txt->setStyleSheet("color:#FFFFFF;");
    ui->lab_pres_txt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->lab_pres_txt->setText("Pressure");
    ui->lab_pres_mm->setFont(ft);
    ui->lab_pres_mm->setStyleSheet("color:#FFFFFF;");
    ui->lab_pres_mm->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->lab_pres_mm->setText("KPa");

    ft.setPointSize(38);
    ui->lcdNum_pres->setFont(ft);
    ui->lcdNum_pres->setStyleSheet("border-radius:5px;font-size:90px;color:#000000;background:#FFFFFF;border-image:url(:/png/lcd_back.png)");
    ui->lcdNum_pres->setDigitCount(6);
    ui->lcdNum_pres->display(0.88);

    ft.setPointSize(24);
    ui->lab_title_config->setFont(ft);
    ui->lab_title_config->setStyleSheet("border-radius:5px;color:#FFFFFF;background:rgb(38,104,157);");
    ui->lab_title_config->setAlignment(Qt::AlignCenter);
    ui->lab_title_config->setText("参 数 设 置"); //DuiZhong Position

    ft.setPointSize(16);
    ui->lab_preposi_txt->setFont(ft);
    ui->lab_preposi_txt->setStyleSheet("color:#FFFFFF;");
    ui->lab_preposi_txt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->lab_preposi_txt->setText("零       位");
    ui->lab_preposi_mm->setFont(ft);
    ui->lab_preposi_mm->setStyleSheet("color:#FFFFFF;");
    ui->lab_preposi_mm->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->lab_preposi_mm->setText("mm");
    connect(ui->lineEdit_preposi,SIGNAL(mylineedit_clicked()),this,SLOT(P_show_keyboard()));

    ft.setPointSize(16);
    ui->lab_freq_txt->setFont(ft);
    ui->lab_freq_txt->setStyleSheet("color:#FFFFFF;");
    ui->lab_freq_txt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->lab_freq_txt->setText("控制频率");
    ui->lab_freq_hz->setFont(ft);
    ui->lab_freq_hz->setStyleSheet("color:#FFFFFF;");
    ui->lab_freq_hz->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->lab_freq_hz->setText("Hz");
    connect(ui->lineEdit_freq,SIGNAL(mylineedit_clicked()),this,SLOT(F_show_keyboard())); //true:pre_position,false:control_frequeny

    connect(keyboard,SIGNAL(Ok_button_clicked()),this,SLOT(Get_keyboard_value()));

    ui->lab_brightness_txt->setFont(ft);
    ui->lab_brightness_txt->setStyleSheet("color:#FFFFFF;");
    ui->lab_brightness_txt->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->lab_brightness_txt->setText("Brightness");
    ui->lab_brightness_percent->setFont(ft);
    ui->lab_brightness_percent->setStyleSheet("color:#FFFFFF;");
    ui->lab_brightness_percent->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->lab_brightness_percent->setText("%");
    ui->lab_brightness_txt->setText("增    益");

    ft.setPointSize(38);
    ui->lcdNum_brightness->setFont(ft);
    ui->lcdNum_brightness->setStyleSheet("padding:0px 0px 0px 0px;border-radius:5px;color:#000000;background:#FFFFFF;border-image:url(:/png/lcd_back.png)");
    ui->lcdNum_brightness->setDigitCount(6);
    ui->lcdNum_brightness->display(100);

    ui->HlSlider_brightness->setMaximum(100);
    ui->HlSlider_brightness->setMinimum(1);
    ui->HlSlider_brightness->setTracking(false);
    ui->HlSlider_brightness->setOrientation(Qt::Horizontal);  // 水平方向
    ui->HlSlider_brightness->setSingleStep(1);  // 步长
    ui->HlSlider_brightness->setValue(100);
    ui->HlSlider_brightness->setStyleSheet("QSlider::handle:horizontal{width:50px;background-color:rgb(255,255,255);margin:-11px 0px -11px 0px;border-radius:12px;}"
                                           "QSlider::groove:horizontal{height:50px;background-color:rgb(219,219,219);}"
                                           "QSlider::add-page:horizontal{background-color:rgb(38,104,157);}"
                                           "QSlider::sub-page:horizontal{background-color:rgb(26,217,110);}");

    connect(ui->HlSlider_brightness,SIGNAL(valueChanged(int)),this,SLOT(change_brightness(int)));
    QProcess::execute("./bin/change_brightness"); //亮度调节，0-255

    ft.setPointSize(38);
    target = 0;  //预设中心位置
    ui->lineEdit_preposi->setAlignment(Qt::AlignCenter);
    ui->lineEdit_preposi->setStyleSheet("border-radius:5px;color:#000000;background:#FFFFFF;");//font-size:80px;
    ui->lineEdit_preposi->setFont(ft);
    ui->lineEdit_preposi->setText(QString("%1").arg(target));
    ui->lineEdit_freq->setAlignment(Qt::AlignCenter);
    ui->lineEdit_freq->setStyleSheet("border-radius:5px;font-size:80px;color:#000000;background:#FFFFFF;");
    ui->lineEdit_freq->setFont(ft);
    Control_frequency = 5;
    ui->lineEdit_freq->setText(QString("%1").arg(Control_frequency));

    QString str_brightness = QString("echo 255 > /sys/devices/platform/s3c24xx-pwm.1/pwm-backlight.0/backlight/pwm-backlight.0/brightness");
    QFile date("/bin/change_brightness");
        if(date.open(QFile::WriteOnly|QIODevice::Truncate))
        {
            QTextStream out(&date);
            out<<"#!/bin/sh";
            out<<"\n";
            out<<str_brightness;
        }
        date.close();
    QProcess::execute("./bin/change_brightness");

    ui->Button_logSave->setStyleSheet("border-radius:8px;border-image:url(:/png/log_def.png)");
    ft.setPointSize(16);
    ui->lab_logSave->setFont(ft);
    ui->lab_logSave->setText("Log Save");
    ui->lab_logSave->setStyleSheet("color:#FFFFFF;");
    ui->lab_logSave->setAlignment(Qt::AlignLeft);
    connect(ui->Button_logSave,SIGNAL(pressed()),this,SLOT(button_logsave_pressed()));
    connect(ui->Button_logSave,SIGNAL(released()),this,SLOT(button_logsave_released()));

    //buzzer timer
    QTimerBuzzer = new QTimer(this);
    connect(QTimerBuzzer,SIGNAL(timeout()),this,SLOT(QTimerBuzzermsdell()));
    Zero_p = 0;
    ifq = 5;

    rdb=RATIO;

}

config_widget::~config_widget()
{
    //设备资源解析
    if (fd_buzzer >= 0)
    {
        ::close(fd_buzzer);
        fd_buzzer = -1;
    }
    //定时器资源析构
    if(NULL!=QTimerBuzzer)
    {
        QTimerBuzzer->stop();
        delete QTimerBuzzer;
        QTimerBuzzer=NULL;
    }    //子窗口资源析构

    if(NULL!=keyboard)
    {
        delete keyboard;
        keyboard=NULL;
    }
    if(NULL!=MesDialog)
    {
        delete MesDialog;
        MesDialog=NULL;
    }
    if(NULL!=MesDialog2)
    {
        delete MesDialog2;
        MesDialog2=NULL;
    }
}

void config_widget::button_logsave_pressed()
{
    this->BuzzerOpen();
    ui->Button_logSave->setStyleSheet("border-radius:8px;border-image:url(:/png/log_clicked.png)");
}

void config_widget::button_logsave_released()
{
    QMutexLocker locker(&m_Mutex);
    emit stopManuPWM();
    sleep(1);
    int i=5000;
    while (i)
        {
            i--;
        }
    this->BuzzerClose();
    QProcess::execute("cd /");
    ui->Button_logSave->setStyleSheet("border-radius:8px;border-image:url(:/png/log_def.png)");
    QProcess::execute("./bin/cplog");


    MesDialog2->which_Mesdialog = false;
    MesDialog2->move(this->geometry().x()+340,this->geometry().y()+153);
    if(bt_change_language)
        MesDialog2->ToShowEnglish();
    else
        MesDialog2->ToShowChinese();
    MesDialog2->show();
    emit startManuPWM();
}

void config_widget::button_home_pressed()
{
    this->BuzzerOpen();
    ui->Button_Home->setStyleSheet("border-radius:8px;border-image:url(:/png/homechoose.png)");
}

void config_widget::button_home_released()
{

    emit configWidgetClose();
    ui->Button_Home->setStyleSheet("border-radius:8px;border-image:url(:/png/homedefault.png)");
    con_w_open = false;
    close();
}

void config_widget::P_show_keyboard()
{
    QString str_display = ui->lineEdit_preposi->text();
    keyboard->str_display = str_display;
    keyboard->display_lineedit();
    which_keyboard = true; //true:pre_position,false:control_frequeny
    keyboard->show();
    keyboard->m_fInputValue = 0;
    keyboard->move(this->geometry().x()+650,this->geometry().y()+240);
}

void config_widget::F_show_keyboard()
{
    QString str_display = ui->lineEdit_freq->text();
    keyboard->str_display = str_display;
    keyboard->display_lineedit();
    which_keyboard = false; //true:pre_position,false:control_frequeny
    keyboard->show();
    keyboard->m_fInputValue = 0;
    keyboard->move(this->geometry().x()+650,this->geometry().y()+240);
}

void config_widget::Get_keyboard_value()
{
    float tmp;
    keyboard->getInputValue(tmp);
    if(which_keyboard) //true:pre_position,false:control_frequeny
    {
//        Target_position = tmp;
        target = tmp;
        ui->lineEdit_preposi->setText(QString("%1").arg(tmp));
        Zero_p = target;
//        qDebug()<<"Target_position="<<target;
        //write zero posi
        str_zero = QString::number(Zero_p,6,2);
        QFile date("/bin/center_posi");
            if(date.open(QIODevice::ReadWrite|QIODevice::Text))
            {
                date.write(str_zero.toUtf8());
//                date.write(",");
            }
            date.close();
        //end write zero posi
        emit ChangeTarget();
    }
    else
    {
//        qDebug()<<"tmp="<<(int)tmp;
        if(((int)tmp<1)||((int)tmp>11) )
        {
            MesDialog->which_Mesdialog = true;
            MesDialog->move(this->geometry().x()+340,this->geometry().y()+153);
            if(bt_change_language)
                MesDialog->ToShowEnglish();
            else
                MesDialog->ToShowChinese();
            MesDialog->show();
            qDebug()<<"Control_frequency="<<ifq;
        }
        else
        {
            ifq = (int)tmp;
            ui->lineEdit_freq->setText(QString("%1").arg(ifq));
            qDebug()<<"Control_frequency="<<ifq;
        }
    }
}

void config_widget::change_brightness(int value)
{
    /*
    emit stopManuPWM();
    int tmp;
    QProcess::execute("cd");
    ui->lcdNum_brightness->display(value);
    tmp = (int)(value*255/100);
    QString str_brightness = QString("echo %1 > /sys/devices/platform/s3c24xx-pwm.1/pwm-backlight.0/backlight/pwm-backlight.0/brightness").arg(tmp);
    QFile date("change_brightness");
        if(date.open(QFile::WriteOnly|QIODevice::Truncate))
        {
            QTextStream out(&date);
            out<<"#!/bin/sh";
            out<<"\n";
            out<<str_brightness;
        }
        date.close();
    QProcess::execute("./change_brightness");
    emit startManuPWM();
  */
    if(rdb == LIGHT){
        QMutexLocker locker(&m_Mutex);
        int tmp;
        ui->lcdNum_brightness->display(value);
        tmp = (int)(value*255/100);
        QFile date("/sys/devices/platform/s3c24xx-pwm.1/pwm-backlight.0/backlight/pwm-backlight.0/brightness");
            if(date.open(QFile::WriteOnly|QIODevice::Truncate))
            {
                QTextStream out(&date);
                out<<tmp;
            }
            date.close();
    }
    else{
        Setpposi.EctlRatio = (int)value;
        ui->lcdNum_brightness->display(int(Setpposi.EctlRatio));
    }

}

void config_widget::ToShowChinese()
{
    QFont ft;
    ft.setPointSize(36);
    ft.setWeight(75);
    ui->lab_title_man->setFont(ft);
    ui->lab_title_man->setText("振 动 台 数 字 自 动 对 中 系 统"); //Digital Automatic Alignment System of Plain Jolter

    ft.setPointSize(24);
    ui->lab_title_posi->setFont(ft);
    ui->lab_title_posi->setText("当 前 状 态"); //now state
    ft.setPointSize(24);
    ui->lab_title_config->setFont(ft);
    ui->lab_title_config->setText("参 数 设 置");  //Config
    ui->lab_absp_txt->setFont(ft);
    ui->lab_absp_txt->setText("当前位置"); //Abs position
    ui->lab_absp_mm->setFont(ft);
    ui->lab_absp_mm->setText("mm");
    ui->lab_pres_txt->setFont(ft);
    ui->lab_pres_txt->setText("气压值");  //Pressure value
    ui->lab_pres_mm->setFont(ft);
    ui->lab_pres_mm->setText("KPa"); //KPa
    ui->lab_preposi_txt->setFont(ft);
    ui->lab_preposi_txt->setText("零       位"); //Pre position
    ui->lab_preposi_mm->setFont(ft);
    ui->lab_preposi_mm->setText("mm");
    ui->lab_freq_txt->setFont(ft);
    ui->lab_freq_txt->setText("控制频率"); //control frequency
    ui->lab_freq_hz->setFont(ft);
    ui->lab_freq_hz->setText("Hz");
    ui->lab_brightness_percent->setFont(ft);
    ui->lab_brightness_percent->setText("%"); //Screen brightness
    ui->lab_brightness_txt->setFont(ft);
    ui->lab_brightness_txt->setText("频幕亮度");
    ui->lab_home->setFont(ft);
    ui->lab_home->setText("主界面"); //Home
    ui->lab_logSave->setFont(ft);
    ui->lab_logSave->setText("导出日志"); //log
}

void config_widget::ToShowEnglish()
{
    QFont ft;
    ft.setPointSize(36);
    ft.setWeight(75);
#ifdef WINDOWS
    ft.setPointSize(24);
#endif
    ui->lab_title_man->setFont(ft);
    ui->lab_title_man->setText("Digital Automatic Alignment System of Plain Jolter");
    ft.setPointSize(24);
    ui->lab_title_posi->setFont(ft);
    ui->lab_title_posi->setText("Current state"); //Abs position
    ft.setPointSize(24);
#ifdef WINDOWS
    ft.setPointSize(16);
#endif
    ft.setPointSize(24);
    ui->lab_title_config->setFont(ft);
    ui->lab_title_config->setText("Config");  //Config
#ifdef WINDOWS
    ft.setPointSize(16);
#endif
    ui->lab_absp_txt->setFont(ft);
    ui->lab_absp_txt->setText("Current position"); //Abs position
    ui->lab_absp_mm->setFont(ft);
    ui->lab_absp_mm->setText("mm");
    ui->lab_pres_txt->setFont(ft);
    ui->lab_pres_txt->setText("Pressure value");  //Pressure value
    ui->lab_pres_mm->setFont(ft);
    ui->lab_pres_mm->setText("KPa"); //KPa
    ui->lab_preposi_txt->setFont(ft);
    ui->lab_preposi_txt->setText("Zero     position"); //Pre position
    ui->lab_preposi_mm->setFont(ft);
    ui->lab_preposi_mm->setText("mm");
    ui->lab_freq_txt->setFont(ft);
    ui->lab_freq_txt->setText("Control frequency"); //control frequency
    ui->lab_freq_hz->setFont(ft);
    ui->lab_freq_hz->setText("Hz");
    ui->lab_brightness_percent->setFont(ft);
    ui->lab_brightness_percent->setText("%"); //Screen brightness
    ui->lab_brightness_txt->setFont(ft);
    ui->lab_brightness_txt->setText("Screen brightness");
    ui->lab_home->setFont(ft);
    ui->lab_home->setText("Home"); //Home
    ui->lab_logSave->setFont(ft);
    ui->lab_logSave->setText("Log Save"); //Log Save
}

void config_widget::ReDisplayScreen()
{
    str_posi = QString::number(posi,6,2);
    str_pres = QString::number(pres,6,2);
    str_zero = QString::number(Zero_p,6,2);
    ui->lcdNum_absp->display(str_posi);
    ui->lcdNum_pres->display(str_pres);
    ui->lineEdit_preposi->setText(str_zero);
}

void config_widget::BuzzerOpen()
{
    QTimerBuzzer->start(1);
#ifdef UBUNTU
#ifdef OPENBUZZER
    ioctl(fd_buzzer,1,0);
#endif
#endif
}

void config_widget::BuzzerClose()
{
#ifdef UBUNTU
#ifdef OPENBUZZER
    ioctl(fd_buzzer,0,0);
#endif
#endif
}

void config_widget::QTimerBuzzermsdell()
{
    QMutexLocker locker(&m_Mutex);
    this->BuzzerClose();
    QTimerBuzzer->stop();
}


void config_widget::on_pb_zylight_pressed()
{
    Useposi.RorL = !Useposi.RorL;
    if(Useposi.RorL){  //增益
        ui->pb_zylight->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_zy.png)");
        ui->lab_brightness_txt->setText("增    益");
        rdb=RATIO;
        qDebug()<<"###RATIO ###"<<rdb;
    }
    else{  //亮度
        ui->pb_zylight->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_lighe.png)");
        ui->lab_brightness_txt->setText("频幕亮度");
        rdb=LIGHT;
        qDebug()<<"###LIGHT ###"<<rdb;
    }

}
