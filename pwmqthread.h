#ifndef PWMQTHREAD_H
#define PWMQTHREAD_H
#include "commmacro.h"
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include <QDateTime>
#include <QPoint>
#include <QFile>
#include <QPushButton>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#ifdef UBUNTU
#include <net/if.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <termio.h>
#include <linux/rtc.h>
#include <poll.h>
#include "spi.h"
#include "cstdlib"
#include <termio.h>
#endif
#include <math.h>
#include "math.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include "mywidget.h"
#include "config_widget.h"
#include <QQueue>

class PwmqThread : public QObject
{
    Q_OBJECT
public:
    explicit PwmqThread(QObject *parent = 0);

    int fd_MyPwm1;
    int fd_AdSpi;
    bool ToStop;
    bool AorM;  //true:自动  false:手动
       //for  ad7606_read(int fd), get ad7606 numbers
    volatile double posi,v_posi,posi_1,posi_2,posi_3,posi_4;
    volatile double pres;
    unsigned char ad_bf[6];
    double a;//低通滤波系数 时间常数a越大，滞后越低，但是截止频率越高 a = 2*fL*PI*t
    double Yn,Yn_1;
    double Yn1,Yn1_1;
    volatile double Ave_posi;//经过滤波后输出值
    volatile double Sum_posi;//经过滤波后输出值
    long int OutCount;
    long int InCount;

    double Height;      //梯形块高度
    double Width;       //梯形块宽度
    double HalfRange;   //一半量程
    double target;  //正新零位

    int OutCtlfreq; //出气控制频率
    int InCtlfreq;//进气控制频率
    int CutOffreq;  //截止频率
    double InChange; //进气变化阀值
    double OutChange;//出气变化阀值
    double CtlAccu;  //控制精度
    int EctlRatio;  //电对中比例控制
    float OutV; //输出电压

    float pidoutV;  //from gas

    QQueue<double> QavePosi;
    QQueue<double> Qqyn1;
    double p_avposi;
    int countEmg;  //延时启动突发情况数据保存
    bool isOKtoEMG; //突发情况数据保存开关
    int fd_ttySAC1; //for 485 uart
    int fd_485ctlp; //for 485 ctl pin 1:senddata 0:recivedata
    double pZero;

    int pcont;


public:
    void Device_init();
    void Ad7606_HighRead();
    void Ad7606_LowRead();

    void dataHighGet(double dposi);

    //add by zw for 485
    void RS485SendData(double send);
    int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop);
    unsigned int crc_chk(unsigned char *data,unsigned char length);
    void RS485_SetRange();
    void RS485_SetVoltage(float v);
    void RS485_SetPidVoltage(float v);
    //add end

signals:
    void start_pid();

public slots:
    void Manu_PWM();

};

#endif // PWMQTHREAD_H
