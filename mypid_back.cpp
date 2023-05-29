#include "mypid.h"
#include "QDebug"
#include "math.h"

extern QMutex m_Mutex;
extern double ctlaccu;
extern USEPOSI Useposi;

MyPID::MyPID()
{



}

MyPID::~MyPID()
{

}

void MyPID::PidInit()
{
    /***************************PID canshu inint**********************************************/
//    空载pid参数
//    P = 0.8;
//    I = 1;
//    D = 0.5;

//    100kg负载pid参数
    P = 0.09;
    I = 0.19;
    D = 0.1;

    maxlimitA = 5;    //mm
    minlimitA = -5;   //mm
    maxlimitB = 2;    //mm
    minlimitB = -2;   //mm
    x = 0;
//    target = 50;
//    target = 11.5; //mm 梯形宽度中心值 mainwindow显示中同步修改
    target = 27.6; //mm 梯形高度中心值
    Target_position = 0;
    out = 0;            //ms
    Direction =  -1;
    OpenSize = 0;
    State_PID = -1;

    /***************************error  inint**********************************************/
    Cerror = 0;
    Perror = 0;
    Lerror = 0;
    Cum_Cerror = 0;
    abs_Cerror = 0;
    qDebug()<<"MyPID controller init success!";
}

int MyPID::PIDcontroller(double nowpoint)
{
//    qDebug()<<"###this is PID_Controller###";
    double Increat;
//    Cerror =  target - nowpoint;
    Cerror =  target  - nowpoint;
    abs_Cerror = fabs(Cerror);
//    qDebug()<<"abs_Cerror="<<abs_Cerror;

//    if(abs_Cerror>2)//0.25~2
//    if(abs_Cerror>1)//0.25~2
    if(abs_Cerror>Useposi.CtlAccu)//0.25~2    静态极限0.2mm   动态极限0.3mm   应用范围0.5~1mm 默认1.0mm
    {
        State_PID = 1;
        /*limitA judge**********************************************/
        if(Cerror > maxlimitA)
            Cerror = (double)maxlimitA;
        else if(Cerror < minlimitA)
            Cerror = (double)minlimitA;
        else Cerror = Cerror;
//        qDebug()<<"real Cerror="<<Cerror;

        /*limitB judge  half open or full open**********************************************/
        if((Cerror >= maxlimitB) | (Cerror <= minlimitB))
        {
             OpenSize = 5.0;   //full open
//             qDebug()<<"OpenSize=full open(5V)";
        }
        else
        {
            OpenSize = 2.5;   //full open
//            qDebug()<<"OpenSize=half open(2.5V)";
        }

        /*open direction**********************************************/
        if(Cerror >= 0)
        {
             Direction = 1;   //output
//             qDebug()<<"Direction=open output valve";
        }
        else
        {
             Direction = 0;   //input
//             qDebug()<<"Direction=open input valve";
        }

//        Increat = P *Cerror+D*(Cerror-Perror); //position
//        /*###add by zw 20201218 for PID####*/
//        Cum_Cerror+=fabs(Cerror);
//        if(Cum_Cerror>10) Cum_Cerror = 10;
//        Increat = P *Cerror+I*Cum_Cerror+D*(Cerror-Perror); //position
//        /*##### add end ####*/
        Increat = P *(fabs(Cerror)-Perror)+I*fabs(Cerror)+D*(fabs(Cerror)-2*Perror+Lerror); //increase

//        qDebug()<<"Increat="<<Increat;
//        out = (fabs(Increat)/5.0)*500;
//        if(out > 500) out = 500;
        //add by zw 20221015

//        out = (fabs(Increat)/5.0)*500;
//        if(out > 800) out = 500;

        out = (fabs(Increat)/5.0)*TIMEMAX;
        if(out > TIMEMAX) out = TIMEMAX;


        Lerror = Perror;
        Perror = fabs(Cerror);
//        qDebug()<<"out="<<out;

        return out;
    }
    else
    {
        State_PID = 0;
        return 0;
    }
}

