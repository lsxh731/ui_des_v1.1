#ifndef COMM_MACRO_H
#define COMM_MACRO_H
#include "mywidget.h"
#define UBUNTU
//#define WINDOWS

#define VCOE 1.0
#define TIMEMAX 200

//#define PROG1  //open
#define PROG2  //close

//#define OPENBUZZER
#define POSITION
//#define CLS_K_10
#define HG_C1050
//#define DIRECTION
#include <unistd.h>
#define EMGDATA

#ifdef UBUNTU //Compiler Switch
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <linux/rtc.h>
#endif

#include "qmath.h"
#include <QString>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#define PI 3.1415926
#define TARGET 27.6

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>
#include <QDir>
#pragma execution_character_set("utf-8")

#define PORT 9999
#define UPLOAD_FILE            0x0F01      //上传文件
#define SYN_FILE_LIST          0x0F02      //同步文件列表
#define DOWNLOAD_FILE          0x0F03      //下载文件
#define DELETE_FILE            0x0F04      //删除文件命令



typedef struct SETPOSI{
    double Height;
    double Weight;
    double HalfRange;
    int CutOffreq;
    int EctlRatio;
    double SCtlAccu;
    int SCtlfreq;
    double SInChange;
    double SOutChange;
    double DCtlAccu;
    int DInCtlfreq;
    int DOutCtlfreq;
    double DInChange;
    double DOutChange;
    double VOutMax;
}SETPOSI;

typedef struct USEPOSI{

    double CtlAccu;
    double InChange;
    double OutChange;
    int InCtlfreq;
    int OutCtlfreq;
    bool SorD; //true:S false:D
    bool bGas;  //gas button
    bool bElec;  //elec button
    double vOut;  //电对中输出电压
    bool RorL;  //true:Ratio false:Light
    double VOutMax;
}USEPOSI;


typedef char  int8;
typedef short int16;
typedef int   int32;

static mywidget* MyWidgetHandle;
static int Manu_count;
static bool StopAuto;
static QMutex m_stopMutex;
static volatile bool IsReading;
static volatile int on_time;
static volatile int off_time;
static volatile float Target_position;
static volatile int Control_frequency;
enum rdButton{LIGHT,RATIO};
#endif//COMM_MACRO_H
