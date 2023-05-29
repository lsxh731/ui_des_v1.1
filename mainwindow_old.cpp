#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFont>
#include <QPushButton>
#include <QProcess>
#include <QList>
#include <QTime>


extern QMutex m_Mutex;
bool f_falut;  //zijian falut
bool s_falut;  //yunxing data falut

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    longopen = false;
    con_w->con_w_open = false;
    bt_inout_pressed = false;
    con_w = new config_widget();
    f_falut = true;
    s_falut = false;
    incount = 0;

    /**********************GUI init ***************************************/
    QFont ft;
    ui->setupUi(this);
#ifdef UBUNTU
    this->setWindowFlags(Qt::FramelessWindowHint);
#endif
    ui->Button_in->setEnabled(false);
    ui->Button_out->setEnabled(false);
    ui->Button_config->setEnabled(false);
    ui->Button_change->setEnabled(false);
    ui->Button_language_change->setEnabled(false);
    ui->frame->setObjectName("myframe");
    ui->frame->setStyleSheet("QFrame#myframe{border-image:url(:/png/main_ui.jpg)}" );

    ui->Button_in->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_in_def.jpg)");
    ft.setPointSize(16);
    ui->lab_bt_in->setFont(ft);
    ui->lab_bt_in->setText("INPUT");
//    ui->lab_bt_in->setStyleSheet("color:#FFFFFF;background:#FFEBCD;");
    ui->lab_bt_in->setStyleSheet("color:#FFFFFF;");
    ui->lab_bt_in->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    ui->lab_bt_in->move((int)ui->Button_in->geometry().x(),(int)ui->Button_in->geometry().y()+120);
    connect(ui->Button_in,SIGNAL(pressed()),this,SLOT(button_in_pressed()));
    connect(ui->Button_in,SIGNAL(released()),this,SLOT(button_in_released()));

    ui->Button_out->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_out_def.jpg)");
    ft.setPointSize(16);
    ui->lab_bt_out->setFont(ft);
    ui->lab_bt_out->setText("OUTPUT");
    ui->lab_bt_out->setStyleSheet("color:#FFFFFF;");
    ui->lab_bt_out->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    ui->lab_bt_out->move((int)ui->Button_out->geometry().x(),(int)ui->Button_out->geometry().y()+120);
    connect(ui->Button_out,SIGNAL(pressed()),this,SLOT(button_out_pressed()));
    connect(ui->Button_out,SIGNAL(released()),this,SLOT(button_out_released()));

    bt_stop_state = false;      //false:stop;true:start
    ui->Button_stop->setStyleSheet("border-radius:8px;border-image:url(:/png/start.jpg)");
    ft.setPointSize(16);
    ui->lab_bt_stop->setFont(ft);
    ui->lab_bt_stop->setText("开始");
    ui->lab_bt_stop->setStyleSheet("color:#FFFFFF;");
    ui->lab_bt_stop->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    ui->lab_bt_stop->move((int)ui->Button_stop->geometry().x(),(int)ui->Button_stop->geometry().y()+120);
    connect(ui->Button_stop,SIGNAL(pressed()),this,SLOT(button_stop_pressed()));
    connect(ui->Button_stop,SIGNAL(released()),this,SLOT(button_stop_released()));


//    bt_change_state = false;//false:menu,true:auto
    ui->Button_change->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_change_manu_chinese.png)");
    ft.setPointSize(16);
    ui->lab_bt_change->setFont(ft);
    ui->lab_bt_change->setText("Auto/Manu");
    ui->lab_bt_change->setStyleSheet("color:#FFFFFF;");
    ui->lab_bt_change->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
    ui->lab_bt_change->move((int)ui->Button_change->geometry().x(),(int)ui->Button_change->geometry().y()+120);
    connect(ui->Button_change,SIGNAL(pressed()),this,SLOT(button_change_pressed()));

    bt_change_language = false;//false:chinese,true:english
    ui->Button_language_change->setStyleSheet("border-radius:8px;border-image:url(:/png/l_chinese.jpg)");
    connect(ui->Button_language_change,SIGNAL(pressed()),this,SLOT(button_language_pressed()));

    ui->Button_config->setStyleSheet("border-radius:8px;border-image:url(:/png/conf.png)");
    connect(ui->Button_config,SIGNAL(pressed()),this,SLOT(button_config_pressed()));
    connect(ui->Button_config,SIGNAL(released()),this,SLOT(button_config_released()));
    ft.setPointSize(14);
    ui->lab_config->setFont(ft);
    ui->lab_config->setAlignment(Qt::AlignLeft);
    ui->lab_config->setStyleSheet("color:#FFFFFF;");
    ui->lab_config->setText("CONFIG");

//    ft.setPointSize(26);
    ft.setPointSize(36);
    ft.setWeight(75);
    ui->lab_title_man->setFont(ft);
    ui->lab_title_man->setStyleSheet("color:#FFFFFF;");
    ui->lab_title_man->setAlignment(Qt::AlignCenter);
    ui->lab_title_man->setText("振 动 台 数 字 自 动 对 中 系 统"); //Digital Automatic Alignment System of Plain Jolter


//    ft.setPointSize(16);
    ft.setPointSize(24);
    ft.setWeight(75);
    ui->lab_title_state->setFont(ft);
//    ui->lab_title_state->setStyleSheet("border-radius:5px;color:#FFFFFF;background:#D3D3D3;");
    ui->lab_title_state->setStyleSheet("border-radius:5px;color:#FFFFFF;background:rgb(38,104,157);");
    ui->lab_title_state->setAlignment(Qt::AlignCenter);
    ui->lab_title_state->setText("对中状态"); //DuiZhong State


//    ft.setPointSize(16);
    ft.setPointSize(24);
    ft.setWeight(75);
    ui->lab_title_posi->setFont(ft);
//    ui->lab_title_posi->setStyleSheet("border-radius:5px;color:#FFFFFF;background:#D3D3D3;");
    ui->lab_title_posi->setStyleSheet("border-radius:5px;color:#FFFFFF;background:rgb(38,104,157);");
    ui->lab_title_posi->setAlignment(Qt::AlignCenter);
    ui->lab_title_posi->setText("对 中 位 置"); //DuiZhong Position

    ft.setPointSize(24);
    ft.setWeight(75);
    ui->lab_title_control->setFont(ft);
//    ui->lab_title_control->setStyleSheet("border-radius:5px;color:#FFFFFF;background:#D3D3D3;");
    ui->lab_title_control->setStyleSheet("border-radius:5px;color:#FFFFFF;background:rgb(38,104,157);");
    ui->lab_title_control->setAlignment(Qt::AlignCenter);
    ui->lab_title_control->setText("对 中 控 制");  //DuiZhong Control

    ft.setPointSize(14);
    ui->lab_sys_title->setFont(ft);
    ui->lab_sys_title->setStyleSheet("color:#FFFFFF;");
    ui->lab_sys_title->setAlignment(Qt::AlignLeft);
    ui->lab_sys_title->setText("Current running state of the system：");

    ft.setPointSize(14);
    ui->lab_sys_txt->setFont(ft);
    ui->lab_sys_txt->setStyleSheet("color:#BBFFFF;");
    ui->lab_sys_txt->setAlignment(Qt::AlignLeft);
    ui->lab_sys_txt->setText("The current system is in manual centering mode");

    ui->lab_light1->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_red.png)");
    ft.setPointSize(12);
    ui->lab_light1_txt->setFont(ft);
    ui->lab_light1_txt->setStyleSheet("color:#FFFFFF;");
    ui->lab_light1_txt->setAlignment(Qt::AlignHCenter|Qt::AlignLeft);
    ui->lab_light1_txt->setText("FAULT");

    ui->lab_light2->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_blank.png)");
    ft.setPointSize(12);
    ui->lab_light2_txt->setFont(ft);
    ui->lab_light2_txt->setStyleSheet("color:#FFFFFF;");
    ui->lab_light2_txt->setAlignment(Qt::AlignCenter|Qt::AlignLeft);
    ui->lab_light2_txt->setText("IN valve");

    ui->lab_light3->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_blank.png)");
    ft.setPointSize(12);
    ui->lab_light3_txt->setFont(ft);
    ui->lab_light3_txt->setStyleSheet("color:#FFFFFF;");
    ui->lab_light3_txt->setAlignment(Qt::AlignCenter|Qt::AlignLeft);
    ui->lab_light3_txt->setText("OUT valve");

    ft.setPointSize(15);
    ui->lab_posi_txt->setFont(ft);
    ui->lab_posi_txt->setStyleSheet("color:#FFFFFF;");
    ui->lab_posi_txt->setAlignment(Qt::AlignCenter);
    ui->lab_posi_txt->setText("Central Postion:");
    ui->lab_posi_mm->setFont(ft);
    ui->lab_posi_mm->setStyleSheet("color:#FFFFFF;");
    ui->lab_posi_mm->setAlignment(Qt::AlignCenter);
    ui->lab_posi_mm->setText("mm");

//    ui->lcdNum_posi->setAttribute(Qt::WA_TranslucentBackground, true);
//    ui->lcdNum_posi->setFrameStyle(QFrame::Panel | QFrame::Raised);
//    ui->lcdNum_posi->setBackgroundRole(QPalette::Background);
//    ui->lcdNum_posi->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNum_posi->setStyleSheet("border-radius:5px;font-size:50px;color:#000000;background:#FFFFFF;border-image:url(:/png/lcd_back.png)");
    ui->lcdNum_posi->setDigitCount(6);
    ui->lcdNum_posi->display(0.00);

    /*########### test ###########*/
//    test_Time = new QTimer(this);
//    test_Time->start(200);
//    connect(test_Time,SIGNAL(timeout()),this,SLOT(test_time_dell()));
    /*
    qDebug()<<"frameGeometrywidth="<<this->frameGeometry().width()<<"frameGeometryheight="<<this->frameGeometry().height();
    qDebug()<<"geometrywidth="<<this->geometry().width()<<"geometryheight="<<this->geometry().height();
    qDebug()<<"x="<<ui->lab_title_posi->geometry().x()<<"y="<<ui->lab_title_posi->geometry().y();
    qDebug()<<"width="<<ui->lab_title_posi->geometry().width()<<"height="<<ui->lab_title_posi->geometry().height();
    */

    /*########### QThreadObject test ###########*/
    this->InitQthreadObject();
    bt_stop_state = true;      //false:stop;true:start
    ui->Button_stop->setStyleSheet("border-radius:8px;border-image:url(:/png/stop.jpg)");
    ui->lab_bt_stop->setText("暂停");
    bt_change_state = true;//false:menu,true:auto

    this->ToShowChinese();

    /*########### QTimer Init ###########*/
    //PID电磁阀控制
    QTimerX = new QTimer(this);
    connect(QTimerX,SIGNAL(timeout()),this,SLOT(QTimerXmsdell()));
    //对中位置，绝对位置，气压值显示刷新
    QtimerScreen = new QTimer(this);
//    QtimerScreen->start(500);
    connect(QtimerScreen,SIGNAL(timeout()),this,SLOT(ReDisplayScreen()));
//    connect(QtimerScreen,SIGNAL(timeout()),con_w,SLOT(ReDisplayScreen()));
    //手动对中模式下5min后休眠，降低采样率;
    Qtimer5min = new QTimer(this);
    connect(Qtimer5min,SIGNAL(timeout()),this,SLOT(Qtimer5mindell()));
    //判断点动还是连续按下;
    QtimerOneOrContinue = new QTimer(this);
    State_OneClick = true;
    connect(QtimerOneOrContinue,SIGNAL(timeout()),this,SLOT(OneOrContinue()));
    //buzzer timer
    QTimerBuzzer = new QTimer(this);
    connect(QTimerBuzzer,SIGNAL(timeout()),this,SLOT(QTimerBuzzermsdell()));
    //AD timer
    QTimerAD = new QTimer(this);
    connect(QTimerAD,SIGNAL(timeout()),this,SLOT(QTimerADdell()));
    Click_Time = new QTimer(this);
    connect(Click_Time,SIGNAL(timeout()),this,SLOT(test_time_dell()));


    /**********************system current time ***************************************/
    QDateTime current_date_time =QDateTime::currentDateTime();
#ifdef UBUNTU
    current_date =current_date_time.toUTC().toString("yyyy-MM-dd hh:mm");
    str_name =current_date_time.toUTC().toString("yyyy-MM-dd-hh-mm");
#else
    current_date =current_date_time.toString("yyyy-MM-dd hh:mm");
    str_name =current_date_time.toString("yyyy-MM-dd-hh-mm");
#endif
    ft.setPointSize(18);
    ui->lab_time->setFont(ft);
    ui->lab_time->setStyleSheet("color:#FFFFFF;");
    ui->lab_time->setText(current_date);

    /**********************system log init ***************************************/
    str_name = QString("./log/logfile-%1.txt").arg(str_name);
    QString print = QString("%1 Rate:2Hz").arg(current_date);
    QFile Log_date(str_name);
    if(Log_date.open(QFile::WriteOnly|QIODevice::Truncate))
    {
        Log_date.write(print.toUtf8());
        Log_date.write("\r\n");
        Log_date.close();
    }

    /*########### Device_init ###########*/
    this->Device_init();

//    ui->lab_light1->close();
//    ui->lab_light1_txt->close();

    this->setAttribute(Qt::WA_AcceptTouchEvents);


    /*########### Print date from linux ###########*/
//    connect(&m_process,SIGNAL(readyReadStandardOutput()),this,SLOT(ReadFromLinux()));
//    m_process.setReadChannel(QProcess::StandardOutput);
//    m_process.start("cmd /c ping /t www.qt.io");
    ui->Button_StarThread->close();
    ui->Button_StopThread->close();

    connect(con_w,SIGNAL(ChangeTarget()),this,SLOT(Change_Target()));

    /*########### test code ###########*/

//    ui->lcdNum_test->display(str_posi);
    connect(ui->Button_test,SIGNAL(pressed()),this,SLOT(test()));
    ui->Button_test->close();
    ui->lcdNum_test->close();
    ui->Button_in->setDown(true);
    ui->Button_stop->hide();
    ui->lab_bt_stop->hide();

    QTimerAD->start(1000); //延时启动自动对中3s

    //QSocketNotifier 用来监听系统文件操作
    //m_notifier = new QSocketNotifier(fd_Valve1, QSocketNotifier::Read, this);
    //connect(m_notifier, SIGNAL(activated(int)), this, SLOT(test()));//add by 2021.08.12
    this->InitTarget();
    this->ReadInitFile();

}


MainWindow::~MainWindow()
{
    //线程资源析构
    if (m_Thread_pwm!=NULL)
    {
        if(m_Thread_pwm->isRunning())
        {
            m_objThread_pwm->ToStop  = true;
            m_Thread_pwm->quit();
            m_Thread_pwm->wait();
        }
        delete m_Thread_pwm;
        m_Thread_pwm = NULL;
    }

    if (m_objThread_pwm!=NULL)
    {
        delete m_objThread_pwm;
        m_objThread_pwm = NULL;
    }
    //设备资源解析
    if (fd_buzzer >= 0)
    {
        ::close(fd_buzzer);
        fd_buzzer = -1;
    }
    if (fd_Valve1 >= 0)
    {
        ::close(fd_Valve1);
        fd_Valve1 = -1;
    }
    if (fd_Valve2 >= 0)
    {
        ::close(fd_Valve2);
        fd_Valve2 = -1;
    }
    if (fd_Myi2c0 >= 0)
    {
        ::close(fd_Myi2c0);
        fd_Myi2c0 = -1;
    }
    if (fd_Myi2c1 >= 0)
    {
        ::close(fd_Myi2c1);
        fd_Myi2c1 = -1;
    }
    if (fd_rtc >= 0)
    {
        ::close(fd_rtc);
        fd_rtc = -1;
    }
    //定时器资源析构
    if(NULL!=Click_Time)
    {
        Click_Time->stop();
        delete Click_Time;
        Click_Time=NULL;
    }
    if(NULL!=QTimerX)
    {
        QTimerX->stop();
        delete QTimerX;
        QTimerX=NULL;
    }
    if(NULL!=QtimerScreen)
    {
        QtimerScreen->stop();
        delete QtimerScreen;
        QtimerScreen=NULL;
    }
    if(NULL!=Qtimer5min)
    {
        Qtimer5min->stop();
        delete Qtimer5min;
        Qtimer5min=NULL;
    }
    if(NULL!=QtimerOneOrContinue)
    {
        QtimerOneOrContinue->stop();
        delete QtimerOneOrContinue;
        QtimerOneOrContinue=NULL;
    }
    if(NULL!=QTimerBuzzer)
    {
        QTimerBuzzer->stop();
        delete QTimerBuzzer;
        QTimerBuzzer=NULL;
    }
    if(NULL!=QTimerAD)
    {
        QTimerAD->stop();
        delete QTimerAD;
        QTimerAD=NULL;
    }
    //子窗口资源析构
    if(NULL!=con_w)
    {
        delete con_w;
        con_w=NULL;
    }
    //主窗口资源析构
    delete ui;
    ui=NULL;

}

void MainWindow::Device_init()
{

#ifdef UBUNTU
    /**********************buzzer Open***************************/
    char *buzzer_node = "/dev/buzzer_ctl";
    if((fd_buzzer = open(buzzer_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
    {
        qDebug()<<"buzzer Open %s failed!";
//        return;
    }
    else
    {
        con_w->fd_buzzer = fd_buzzer;
        printf("buzzer Open success!\n");
    }
    /**********************Valve Open***************************/
    char *valve1_node = "/dev/myvalve1";
    if((fd_Valve1 = open(valve1_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
    {
        qDebug()<<"MyValve 1 Open %s failed!";
//        return;
    }
    else
    {
        printf("MyValve 1 Open success!\n");
    }

    char *valve2_node = "/dev/myvalve2";
    if((fd_Valve2 = open(valve2_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
    {
        qDebug()<<"MyValve 2 Open %s failed!";
//        return;
    }
    else
    {
        printf("MyValve 2 Open success!\n");
    }

    /**********************Myi2c (0 and 1) Open*****************/
//    char *myi2c0_node = "/dev/myi2c0";
//    if((fd_Myi2c0 = open(myi2c0_node, O_RDWR|O_NDELAY))<0)
//    {
//        qDebug()<<"Myi2c0 Open %s failed!";
//        this->PrintLog("Myi2c0 Open failed!\r\n");
//        return;
//    }
//    else
//    {
//        printf("Myi2c0 Open success!\n");
//        this->PrintLog("Myi2c0 Open success!\r\n");
//    }

//    char *myi2c1_node = "/dev/myi2c1";
//    if((fd_Myi2c1 = open(myi2c1_node, O_RDWR|O_NDELAY))<0)
//    {
//        qDebug()<<"Myi2c1 Open %s failed!";
//        this->PrintLog("Myi2c1 Open failed!\r\n");
//        return;
//    }
//    else
//    {
//        printf("Myi2c1 Open success!\n");
//        this->PrintLog("Myi2c1 Open success!\r\n");
//    }

    /**********************Valve  init **************************/
//    myvalve.open_vlave_in(fd_Valve1);
//    myvalve.open_vlave_out(fd_Valve2);
    myvalve.close_valve_in(fd_Valve1);
    myvalve.close_vlave_out(fd_Valve2);

    /*********************Myi2c init ****************************/
//    mcp4725.i2c_in_WriteData(fd_Myi2c0,2.5);
//    mcp4725.i2c_out_WriteData(fd_Myi2c1,2.5);

    /**********************PIDcontroller init *******************/
    mypid.PidInit();
    PidIsWorking = false;
    connect(m_objThread_pwm,SIGNAL(start_pid()),this,SLOT(StarPid()));
#endif
//    QTimerAD->start(5000);
    //add by zw 20210324 for 配置界面参数设置
}

//void MainWindow::StarPid()
//{
////    QMutexLocker locker(&m_Mutex);
////    QCoreApplication::processEvents();
//        if(bt_change_state&(!f_falut))
//        {
//            if(QTimerX->isActive())
//            {
//                QTimerX->stop();
//            }
//            PidIsWorking = true;
//            timeX = mypid.PIDcontroller(m_objThread_pwm->Ave_posi);
//            if((mypid.target-m_objThread_pwm->Ave_posi > m_objThread_pwm->HalfRange)|(m_objThread_pwm->Ave_posi-mypid.target > m_objThread_pwm->HalfRange))
//            {
//                if(!s_falut)
//                {
//                    ui->lab_light1->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_red.png)");
//                    s_falut = true;
//                    if(QTimerX->isActive())
//                    {
//                        QTimerX->stop();
//                    }
//                    this->valve_stop();
//                }
//            }
//            else
//            {
//                if(s_falut)
//                {
//                    ui->lab_light1->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_blank.png)");
//                    s_falut = false;
//                }
//                if(mypid.State_PID)
//                {
//                    if(mypid.abs_Cerror > 4)   //add by zw 20210310 偏移量大时快速对中
//                    {
//                        if(QTimerX->isActive())
//                        {
//                            QTimerX->stop();
//                        }
//                        this->valve_work();
//                    }
//                    else
//                    {
//                        if(QTimerX->isActive())
//                        {
//                            QTimerX->stop();
//                        }
//                        this->valve_work();
//                        if(mypid.Direction == 0)
//                            QTimerX->start(timeX);
//                        if(mypid.Direction == 1)
//                        {
//                           if(mypid.abs_Cerror < 1)
//                               QTimerX->start(timeX);
//                        }
//                    }
//                 }
//                else
//                {
//                    PidIsWorking = false;
//                    this->valve_stop();
//                }
//            }
//         }
//}

void MainWindow::StarPid()
{
        if(bt_change_state&(!f_falut))
        {
            if(QTimerX->isActive())
            {
                QTimerX->stop();
            }
            PidIsWorking = true;
            timeX = mypid.PIDcontroller(m_objThread_pwm->Ave_posi);

                if((mypid.target-m_objThread_pwm->Ave_posi > m_objThread_pwm->HalfRange)|(m_objThread_pwm->Ave_posi-mypid.target > m_objThread_pwm->HalfRange))
                {
                    ui->lab_light1->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_red.png)");
                    s_falut = true;
                    if(QTimerX->isActive())
                    {
                        QTimerX->stop();
                    }
                    this->valve_stop();
                }
                else
                {
                    ui->lab_light1->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_blank.png)");
                    s_falut = false;
                    if(mypid.State_PID)
                    {
                        if(QTimerX->isActive())
                        {
                            QTimerX->stop();
                        }
                        if(mypid.abs_Cerror > 5)   //add by zw 20210310 偏移量大时快速对中  ±50范围内PID控制
                        {
                            this->valve_work();
                        }
                        else
                        {
                            this->valve_work();
                            if(mypid.Direction == 0)   //进气
                                {
                                    if(incount==0)
                                        QTimerX->start(timeX);
                                    else
                                    {
                                        this->valve_stop();
                                        QTimerX->stop();
                                    }
                                    incount++;
                                    if(incount>3)
                                        incount=0;
                                }

                            if(mypid.Direction == 1)
                                if(mypid.abs_Cerror < 3)
                                    QTimerX->start(timeX);  //放气
                        }
                     }
                    else
                    {
                        PidIsWorking = false;
                        this->valve_stop();
                        QTimerX->stop();
                    }
                }

         }
}

void MainWindow::QTimerXmsdell()
{
//    PidIsWorking = false;
    this->valve_stop();
    if(QTimerX->isActive())
    {
        QTimerX->stop();
    }
}

void MainWindow::valve_work()
{
    if(this->mypid.Direction == 0)   //input
    {
        this->valve_in_work();
        this->valve_out_stop();
    }
    else if(this->mypid.Direction == 1) //output
    {
        this->valve_out_work();
        this->valve_in_stop();
    }
}

void MainWindow::valve_stop()
{
    this->valve_in_stop();
    this->valve_out_stop();
}

void MainWindow::valve_in_work()
{
//    mcp4725.i2c_in_WriteData(fd_Myi2c0,mypid.OpenSize);
    myvalve.open_vlave_in(fd_Valve1);
    ui->lab_light2->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_green.png)");
}

void MainWindow::valve_out_work()
{
//    mcp4725.i2c_out_WriteData(fd_Myi2c1,mypid.OpenSize);
    myvalve.open_vlave_out(fd_Valve2);
    ui->lab_light3->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_green.png)");
}

void MainWindow::valve_in_stop()
{
//    mcp4725.i2c_in_WriteData(fd_Myi2c0,0);
    myvalve.close_valve_in(fd_Valve1);
    ui->lab_light2->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_blank.png)");
}

void MainWindow::valve_out_stop()
{
//    mcp4725.i2c_out_WriteData(fd_Myi2c1,0);
    myvalve.close_vlave_out(fd_Valve2);
    ui->lab_light3->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_blank.png)");
}

void MainWindow::OneOrContinue()
{
    State_OneClick = false;
}

void MainWindow::button_in_pressed()
{
    QMutexLocker locker(&m_Mutex);
    if(!bt_inout_pressed)
    {
        bt_inout_pressed = true;
        ui->Button_in->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_in_clicked.jpg)");
        this->valve_stop();
        this->valve_in_work();
    }
}

void MainWindow::button_in_released()
{
    QMutexLocker locker(&m_Mutex);
    ui->Button_in->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_in_def.jpg)");
    Click_Time->start(500);
//    this->valve_stop();
}

void MainWindow::button_out_pressed()
{
    QMutexLocker locker(&m_Mutex);
    if(!bt_inout_pressed)
    {
        bt_inout_pressed = true;
        ui->Button_out->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_out_clicked.jpg)");
        this->valve_stop();
        this->valve_out_work();
    }
}

void MainWindow::button_out_released()
{
    QMutexLocker locker(&m_Mutex);
    ui->Button_out->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_out_def.jpg)");
    Click_Time->start(500);
//    this->valve_stop();
}

void MainWindow::button_stop_pressed()
{
//    QMutexLocker locker(&m_Mutex);
//    ui->Button_stop->setStyleSheet("border-radius:8px;border-image:url(:/png/stop.jpg)");
    this-> BuzzerOpen();
}

void MainWindow::button_stop_released()
{
//    QMutexLocker locker(&m_Mutex);
    bt_stop_state = !bt_stop_state;
    if(bt_stop_state)      //false:stop;true:start
    {
        ui->Button_stop->setStyleSheet("border-radius:8px;border-image:url(:/png/stop.jpg)");
        if(bt_change_language) //false:chinese,true:english
            ui->lab_bt_stop->setText("STOP");
        else
            ui->lab_bt_stop->setText("暂停");
        this->StarQthreadObject();
        usleep(100000);
        emit Start_PWM();
    }
    else
    {
        ui->Button_stop->setStyleSheet("border-radius:8px;border-image:url(:/png/start.jpg)");
        if(bt_change_language) //false:chinese,true:english
            ui->lab_bt_stop->setText("START");
        else
            ui->lab_bt_stop->setText("启动");
        this->StopQthreadObject();
        usleep(100000);
        emit Start_PWM();
    }
}

void MainWindow::Qtimer5mindell()
{
//    this->StopQthreadObject();
//    usleep(10000);
//    emit Start_PWM();
    m_objThread_pwm->AorM = false;
//    this->StarQthreadObject();
//    usleep(10000);
//    emit Start_PWM();
   if(Qtimer5min->isActive())
   {
       Qtimer5min->stop();
   }
}

void MainWindow::button_change_pressed()
{
    QMutexLocker locker(&m_Mutex);
    if(Click_Time->isActive())
    {
        Click_Time->stop();
    }
    if(QTimerX->isActive())
    {
        QTimerX->stop();
    }
    this->valve_stop();
//    this->BuzzerOpen();
//    QtimerOneOrContinue->stop();
    bt_change_state = !bt_change_state;

    if(bt_change_state) //false:menu,true:auto
    {
        m_objThread_pwm->AorM = true;
        if(Qtimer5min->isActive())
        {
            Qtimer5min->stop();
        }
        //Disable button_in、button_out、button_config
        ui->Button_in->setEnabled(false);
        ui->Button_out->setEnabled(false);
        ui->Button_config->setEnabled(false);

//        if(!m_objThread_pwm->AorM)
//        {
//            this->StopQthreadObject();
//            usleep(10000);
//            emit Start_PWM();
//            m_objThread_pwm->AorM = true;
//            this->StarQthreadObject();
//            usleep(10000);
//            emit Start_PWM();
//        }
        //开启自动对中模式
        StopAuto = false;

        if(bt_change_language) //false:chinese,true:english
        {
            ui->Button_change->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_change_auto_english.png)");
            ui->lab_sys_txt->setText("The current system is in automatic centering mode");
        }
        else
        {
            ui->Button_change->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_change_auto_chinese.png)");
            ui->lab_sys_txt->setText("当前系统处于自动对中模式");
        }
    }
    else
    {
        if(s_falut|f_falut)
        {
            ui->lab_light1->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_blank.png)");
            f_falut = false;
            s_falut = false;
        }
        //Enable button_in、button_out、button_config
        ui->Button_in->setEnabled(true);
        ui->Button_out->setEnabled(true);
        ui->Button_config->setEnabled(true);
        Qtimer5min->start(5*60*1000);
        //关闭自动对中模式
        StopAuto = true;
        PidIsWorking = false;
        if(bt_change_language) //false:chinese,true:english
        {
            ui->Button_change->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_change_manu_english.png)");
            ui->lab_sys_txt->setText("The current system is in manual centering mode");
        }
        else
        {
            ui->Button_change->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_change_manu_chinese.png)");
            ui->lab_sys_txt->setText("当前系统处于手动对中模式");
        }
    }
}

void MainWindow::button_config_pressed()
{
    QMutexLocker locker(&m_Mutex);
    if(Click_Time->isActive())
    {
        Click_Time->stop();
    }
    this->valve_stop();
    ui->Button_config->setStyleSheet("border-radius:8px;border-image:url(:/png/config_clicked.jpg)");
    this-> BuzzerOpen();
}

void MainWindow::button_config_released()
{
    QMutexLocker locker(&m_Mutex);
    ui->Button_config->setStyleSheet("border-radius:8px;border-image:url(:/png/conf.png)");
    con_w->bt_change_language = bt_change_language;
    if(bt_change_language)   //false:chinese,true:english
        con_w->ToShowEnglish();
    else
        con_w->ToShowChinese();
    this->BuzzerClose();
    con_w->show();
    con_w->con_w_open = true;
}

void MainWindow::button_language_pressed()
{
//    QMutexLocker locker(&m_Mutex);
    this-> BuzzerOpen();
    bt_change_language = !bt_change_language;
    if(bt_change_language)
        {
            ui->Button_language_change->setStyleSheet("border-radius:8px;border-image:url(:/png/l_english.jpg)");
            this->ToShowEnglish();
        }
    else
        {
            ui->Button_language_change->setStyleSheet("border-radius:8px;border-image:url(:/png/l_chinese.jpg)");
            this->ToShowChinese();
        }
}

void MainWindow::ToShowChinese()
{
    QFont ft;
    ft.setPointSize(36);
    ft.setWeight(75);
    ui->lab_title_man->setFont(ft);
    ui->lab_title_man->setText("振 动 台 数 字 自 动 对 中 系 统"); //Digital Automatic Alignment System of Plain Jolter
    ui->lab_posi_txt->setFont(ft);
    ui->lab_posi_txt->setText("中心位置："); //Central Postion:
    ui->lab_posi_mm->setFont(ft);
    ui->lab_posi_mm->setText("mm");

    ft.setPointSize(24);
    ui->lab_title_posi->setFont(ft);
    ui->lab_title_posi->setText("对 中 位 置"); //DuiZhong Position
    ft.setPointSize(24);
    ui->lab_title_state->setFont(ft);
    ui->lab_title_state->setText("阀门状态"); //DuiZhong State
    ft.setPointSize(24);
    ui->lab_title_control->setFont(ft);
    ui->lab_title_control->setText("对 中 控 制");  //DuiZhong Control
    ui->lab_light1_txt->setFont(ft);
    ui->lab_light1_txt->setText("故障灯"); //Position
    ui->lab_light2_txt->setFont(ft);
    ui->lab_light2_txt->setText("进气阀");  //IN valve
    ui->lab_light3_txt->setFont(ft);
    ui->lab_light3_txt->setText("出气阀");  //OUT valve
    ui->lab_bt_change->setFont(ft);
    ui->lab_bt_change->setText("手动/自动"); //Auto/Manu
    ui->lab_bt_in->setFont(ft);
    ui->lab_bt_in->setText("进气"); //INPUT
    ui->lab_bt_out->setFont(ft);
    ui->lab_bt_out->setText("出气"); // OUTPUT
    ui->lab_bt_stop->setFont(ft);
    ui->lab_bt_stop->setText("暂停"); //STOP
    ui->lab_sys_title->setFont(ft);
    ui->lab_sys_title->setText("系统当前运行状态："); //Current running state of the system：
    ui->lab_sys_txt->setFont(ft);
    if(bt_change_state) //false:menu,true:auto
        ui->lab_sys_txt->setText("当前系统处于自动对中模式"); //The current system is in manual centering mode
    else
        ui->lab_sys_txt->setText("当前系统处于手动对中模式"); //The current system is in manual centering mode
    ui->lab_config->setFont(ft);
    ui->lab_config->setText("系统配置"); //CONFIG

    if(bt_change_state)  //false:menu,true:auto
        ui->Button_change->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_change_auto_chinese.png)");
    else
        ui->Button_change->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_change_manu_chinese.png)");
    if(bt_stop_state)      //false:stop;true:start
        ui->lab_bt_stop->setText("暂停");
    else
        ui->lab_bt_stop->setText("启动");
}

void MainWindow::ToShowEnglish()
{
    QFont ft;
    ft.setPointSize(36);
    ft.setWeight(75);
#ifdef WINDOWS
    ft.setPointSize(24);
#endif
    ui->lab_title_man->setFont(ft);
    ui->lab_title_man->setText("Digital Automatic Alignment System of Plain Jolter"); //振 动 台 数 字 自 动 对 中 系 统
    ui->lab_posi_txt->setFont(ft);
    ui->lab_posi_txt->setText("Central Postion:"); //中心位置：
    ui->lab_posi_mm->setFont(ft);
    ui->lab_posi_mm->setText("mm");

    ft.setPointSize(24);
    ui->lab_title_posi->setFont(ft);
    ui->lab_title_posi->setText("Position"); //对 中 位 置
    ft.setPointSize(24);
    ui->lab_title_state->setFont(ft);
    ui->lab_title_state->setText("Valve State"); //阀门状态
    ft.setPointSize(24);
#ifdef WINDOWS
    ft.setPointSize(22);
#endif
    ui->lab_title_control->setFont(ft);
    ui->lab_title_control->setText("Control");  //对中控制
    ui->lab_light1_txt->setFont(ft);
    ui->lab_light1_txt->setText("FAULT"); //中心位置
    ui->lab_light2_txt->setFont(ft);
    ui->lab_light2_txt->setText("IN");  //进气阀
    ui->lab_light3_txt->setFont(ft);
    ui->lab_light3_txt->setText("OUT");  //出气阀
    ui->lab_bt_change->setFont(ft);
    ui->lab_bt_change->setText("Auto/Manu"); //自动/手动
    ui->lab_bt_in->setFont(ft);
    ui->lab_bt_in->setText("INPUT"); //进气
    ui->lab_bt_out->setFont(ft);
    ui->lab_bt_out->setText("OUTPUT"); // 出气
    ui->lab_bt_stop->setFont(ft);
    ui->lab_bt_stop->setText("STOP"); //急停
#ifdef WINDOWS
    ft.setPointSize(16);
    ui->lab_sys_title->setFont(ft);
#endif
    ui->lab_sys_title->setText("Current running state of the system:"); //系统当前运行状态：
    ui->lab_sys_txt->setFont(ft);
#ifdef WINDOWS
    ft.setPointSize(16);
    ui->lab_sys_txt->setFont(ft);
#endif
    if(bt_change_state) //false:menu,true:auto
        ui->lab_sys_txt->setText("The current system is in automatic centering mode"); //当前系统处于手动对中模式
    else
        ui->lab_sys_txt->setText("The current system is in manual centering mode"); //当前系统处于手动对中模式
    ui->lab_config->setFont(ft);
    ui->lab_config->setText("CONFIG"); //系统配置

    if(bt_change_state)  //false:menu,true:auto
        ui->Button_change->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_change_auto_english.png)");
    else
        ui->Button_change->setStyleSheet("border-radius:8px;border-image:url(:/png/bt_change_manu_english.png)");
    if(bt_stop_state)      //false:stop;true:start
        ui->lab_bt_stop->setText("STOP");
    else
        ui->lab_bt_stop->setText("START");
}

void MainWindow::ReDisplayScreen()
{
//    QCoreApplication::processEvents();

    double tg;
    tg = 0;
    tg = (double)mypid.target;
    this->GetCurrentTime();
    ui->lab_time->setText(current_date);
//    con_w->posi = m_objThread_pwm->v_posi;
    con_w->posi = m_objThread_pwm->Ave_posi;
    con_w->pres = m_objThread_pwm->pres;

    str_Aveposi = QString::number((tg-m_objThread_pwm->Ave_posi),6,2);
    ui->lcdNum_posi->display(str_Aveposi);

    /*######## str_Aveposi print to log#####*/
    this->PrintLog(str_Aveposi);


//    QCoreApplication::processEvents();
    if(con_w->con_w_open)
        con_w->ReDisplayScreen();
}

void MainWindow::test_time_dell()
{
    if(Click_Time->isActive())
    {
        Click_Time->stop();
    }
    this->valve_stop();
    bt_inout_pressed = false;
}

void MainWindow::InitQthreadObject()
{
        m_Thread_pwm = new QThread();
        m_objThread_pwm = new PwmqThread();
        m_objThread_pwm->moveToThread(m_Thread_pwm);
        sleep(1);
        connect(m_Thread_pwm,SIGNAL(finished()),m_objThread_pwm,SLOT(deleteLater()));
        connect(m_Thread_pwm,SIGNAL(finished()),m_Thread_pwm,SLOT(deleteLater()));

        connect(this,SIGNAL(Start_PWM()),m_objThread_pwm,SLOT(Manu_PWM()));

        connect(con_w,SIGNAL(stopManuPWM()),this,SLOT(StopQthreadObject()));
        connect(con_w,SIGNAL(startManuPWM()),this,SLOT(StarQthreadObject()));
        connect(con_w,SIGNAL(startManuPWM()),m_objThread_pwm,SLOT(Manu_PWM()));

        m_Thread_pwm->start();

}

void MainWindow::StarQthreadObject()
{
    qDebug()<<"MainWindow::StarQthreadObject()";
    IsReading = false;
    m_objThread_pwm->ToStop = false;
}

void MainWindow::StopQthreadObject()
{
    qDebug()<<"MainWindow::StopQthreadObject()";
    m_objThread_pwm->ToStop  = true;
}

void MainWindow::PrintLog(QString str)
{
    QString print = QString("%1\n").arg(str);
    QFile Log_date(str_name);
    if(Log_date.open(QFile::WriteOnly|QIODevice::Append))
    {
       Log_date.write(print.toUtf8());
       Log_date.close();
    }
}

void MainWindow::test()
{
#ifdef UBUNTU
//    QString str_posi;
//    ui->lcdNum_test->display(str_posi);
#endif
//
}

void MainWindow::Change_Target()
{
//    QMutexLocker locker(&m_Mutex);
//    qDebug()<<"con_w->target = "<<con_w->target;
    mypid.target = con_w->target;
    qDebug()<<"mypid.target = "<<mypid.target;
//    TarGet = mypid.target;
//    qDebug()<<"TarGet = "<<TarGet;
}

void MainWindow::BuzzerOpen()
{
    QTimerBuzzer->start(1);
#ifdef UBUNTU
#ifdef OPENBUZZER
    ioctl(fd_buzzer,1,0);
#endif
#endif
}

void MainWindow::BuzzerClose()
{
    if(QTimerBuzzer->isActive())
    {
        QTimerBuzzer->stop();
    }
#ifdef UBUNTU
#ifdef OPENBUZZER
    ioctl(fd_buzzer,0,0);
#endif
#endif
}

void MainWindow::QTimerBuzzermsdell()
{
//    QMutexLocker locker(&m_Mutex);
    this->BuzzerClose();
    if(QTimerBuzzer->isActive())
    {
        QTimerBuzzer->stop();
    }
}

void MainWindow::QTimerADdell()
{
    QtimerScreen->start(500);
    if(QTimerAD->isActive())
    {
        QTimerAD->stop();
    }
    this->StarQthreadObject();
    ui->Button_in->setEnabled(false);
    ui->Button_out->setEnabled(false);
    ui->Button_config->setEnabled(false);
    usleep(100000);
    emit Start_PWM();
    ui->Button_change->setEnabled(true);
    ui->Button_language_change->setEnabled(true);
    this->Self_inspection();

}

void MainWindow::Self_inspection()
{
    double p_old,p_new,p_last;
    sleep(5);
    p_old = m_objThread_pwm->Ave_posi;
    usleep(100000);
    qDebug()<<"p_old = "<<p_old;
    this->valve_in_work();
    qDebug()<<"valve in work";
    usleep(900000);
    this->valve_in_stop();
    usleep(500000);
    qDebug()<<"valve in stop";
    p_new = m_objThread_pwm->Ave_posi;
    qDebug()<<"p_new = "<<p_new;
    this->valve_out_work();
    qDebug()<<"valve out work";
    sleep(2);
    this->valve_out_stop();
    qDebug()<<"valve out stop";
    p_last = m_objThread_pwm->Ave_posi;
    qDebug()<<"p_last = "<<p_last;
    if((fabs(p_new - p_old) > 0.01)|(fabs(p_new - p_last) > 0.01))
    {
        ui->lab_light1->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_blank.png)");
        f_falut = false;
    }
    else
    {
        ui->lab_light1->setStyleSheet("border-radius:8px;border-image:url(:/png/gct_ied_red.png)");
        f_falut = true;
    }
//    QTimer200ms->start(200);
}

void MainWindow::GetCurrentTime()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
#ifdef UBUNTU
    current_date =current_date_time.toUTC().toString("yyyy-MM-dd hh:mm");
#else
    current_date =current_date_time.toString("yyyy-MM-dd hh:mm");
#endif

}

void MainWindow::InitTarget()
{
    QString tips;
    double tmp;
    QFile date("/bin/center_posi");
        if(date.open(QIODevice::ReadWrite|QIODevice::Text))
        {
            QTextStream in(&date);
            tips = in.readAll();
            tmp = tips.toDouble();
            qDebug()<<"##########center position  = "<<tmp<<"##########";
            mypid.target = tmp;
            qDebug()<<"##########mypid.target = "<<mypid.target<<"##########";
            con_w->Zero_p = tmp;
            qDebug()<<"##########con_w->Zero_p = "<<con_w->Zero_p<<"##########";
            m_objThread_pwm->target = tmp;
            qDebug()<<"##########m_objThread_pwm = "<<m_objThread_pwm->target<<"##########";

        }
        date.close();
}

bool MainWindow::ReadInitFile()
{
    double tmp;
    QString filepathname="./qt4.7.1/posiset.ini";
    QFile file(filepathname);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }

    QStringList linelist;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        linelist.push_back(line);
    }
    if(linelist.size()!=3)
    {
        return false;
    }

    QString strTmp;
    strTmp=linelist.at(0);
    strTmp.remove(QRegExp("Height="));//梯形块高度
    tmp=strTmp.toDouble();
    m_objThread_pwm->Height = tmp;
    qDebug()<<"##########Height = "<<tmp<<"##########";

    strTmp=linelist.at(1);
    strTmp.remove(QRegExp("Weight=")); //梯形块宽度
    tmp = strTmp.toDouble();
    m_objThread_pwm->Width = tmp;
    qDebug()<<"##########Width = "<<tmp<<"##########";

    strTmp=linelist.at(2);
    strTmp.remove(QRegExp("HalfRange="));//一半量程
    tmp=strTmp.toDouble();
    m_objThread_pwm->HalfRange = tmp;
    qDebug()<<"##########HalfRange = "<<tmp<<"##########";

    file.close();//关闭文件
    return true;
}



//void MainWindow::ReadFromLinux()
//{
//    this->PrintLog(m_process.readAllStandardOutput());
//}

//QProcess::execute("cd /");
//QProcess::execute("reboot");
//QProcess::execute("echo 255 > /sys/devices/platform/s3c24xx-pwm.1/pwm-backlight.0/backlight/pwm-backlight.0/brightness"); //亮度调节，0-255


//bool MainWindow::event(QEvent *event)
//{
//    switch( event->type() )
//        {
//        case QEvent::TouchBegin:
//           {
//              QTouchEvent* touch = static_cast<QTouchEvent*>(event);
//              touch->touchPoints().at(0).pos().x();
//              qDebug()<<"pos().x()"<<touch->touchPoints().at(0).pos().x();
//              qDebug()<<"pos().y()"<<touch->touchPoints().at(0).pos().y();
//              event->accept();
//              return true;
//           }
//        return MainWindow::event(event);
//        }
//}
