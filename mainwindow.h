#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "config_widget.h"
#include"keyboarddlg.h"
#include <QTimer>
#include <QThread>
#include "valve.h"
#include "mypid.h"
#include "mybutton.h"
#include "myi2c.h"

#include <QEvent>
#include <QFile>
#include <QProcess>
#include "mesdialog.h"
#include "pwmqthread.h"
#include <QMutex>
#include <QMutexLocker>
#include <unistd.h>
#include <qsocketnotifier.h>
#include <QSocketNotifier>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QFile Log_date;           //日志文件
    QString current_date;     //当前时间
    QString str_name;         //本次文件保存名称
    bool bt_change_state;     //false:menu,true:auto
    bool bt_change_language;  //false:chinese,true:english
    bool bt_in_or_out;        //for手动电动模式,false:in,true:out
    bool State_OneClick;      //false:continue;true:one_click
    bool bt_stop_state;      //false:stop;true:start
    bool PidIsWorking;      //false:stop;true:working
    bool longopen;           //teue:longopen.  false:shortopen
    bool bt_inout_pressed;   //true:pressed  false:no


#ifdef UBUNTU
    struct rtc_time rtc_tm;   //rtc
#endif

    QMutex MutexMain;
    config_widget *con_w;

    int fd_buzzer;
    int fd_Valve1,fd_Valve2;
    int fd_Myi2c0;
    int fd_Myi2c1;
    int fd_rtc;
    int fd_i2cdev;
    Valve myvalve;
    MyPID mypid;
    MyI2C mcp4725;
    int timeX; //PID输出值，为经过PID运算后一个周期电磁阀打开的时间，单位/ms;

    QString str_Aveposi;
    QString str_posi;

    int incount; //进气次数

//    QProcess m_process;

public:
    QTimer *Click_Time;
    QTimer *QTimerX;
    QTimer *QtimerScreen;
    QTimer *Qtimer5min;
    QTimer *QtimerOneOrContinue;
    QTimer *QTimerBuzzer;
    QTimer *QTimerAD;

private slots:
    void button_in_pressed();
    void button_in_released();
    void button_out_pressed();
    void button_out_released();
    void button_stop_pressed();
    void button_stop_released();
    void button_change_pressed();
    void button_config_pressed();
    void button_config_released();
    void button_language_pressed();

    /*### 定时器处理函数 ###*/
    void test_time_dell();
    void QTimerXmsdell();
    void ReDisplayScreen();
    void Qtimer5mindell();
    void OneOrContinue();
    void QTimerBuzzermsdell();
    void QTimerADdell();


    void StarQthreadObject();
    void StopQthreadObject();

    void StarPid();
    void test();

    void Change_Target();

//    void ReadFromLinux();

    void on_Button_model_pressed();

    void on_Button_gas_pressed();

    void on_Button_elec_pressed();

signals:
    void Start_PWM();

public:
    void ToShowChinese();
    void ToShowEnglish();

    void InitQthreadObject();

    void Device_init();

    void valve_work();
    void valve_in_work();
    void valve_out_work();
    void valve_stop();
    void valve_in_stop();
    void valve_out_stop();

    void PrintLog(QString str);
    void BuzzerOpen();
    void BuzzerClose();
    void GetCurrentTime();
    void Self_inspection();

    void InitTarget();
    bool ReadInitFile();

private:
    Ui::MainWindow *ui;

    QThread* m_Thread;
    PwmqThread* m_objThread_pwm;
    QThread* m_Thread_pwm;



protected:
//    bool event(QEvent *event);
public:
    //QSocketNotifier *m_notifier;

public:
    void initServer();
    void sendFile();
    void getRemoteFileList();
    void clearVar();
    QString clearFilePath(QString filePath);
    void onStart();
public slots:
    void onReceiveProgress();
    void onAcceptConnected();
    void onUpdateSendProgress(qint64 numBytes);
    void displayError(QAbstractSocket::SocketError socketError);
private:
    QTcpServer    *m_tcpServer;
    QTcpSocket    *m_tcpSocket;
    QFile         *m_localFile;
    QString       m_fileName;
    qint64        m_fileNameSize;
    qint64        m_totalBytes;
    qint64        m_bytesReceived;
    QByteArray    m_inBlock;
    qint64        m_bytesWritten;
    qint64        m_bytesTobeWrite;
    QByteArray    m_outBlock;
    qint64        m_payLoadSize;
    qint64        m_cmd;

};

#endif // MAINWINDOW_H
