#ifndef MYPID_H
#define MYPID_H
#include "commmacro.h"

class MyPID
{
public:
    MyPID();
    ~MyPID();

    int PIDcontroller(double nowpoint);
    void PidInit();


public slots:


protected:

public:

    float P,I,D;
    int maxlimitA,minlimitA;      //-5mm~5mm
    int maxlimitB,minlimitB;      //-3mm~3mm
    int x;    //D kaiguan
    volatile float target;
    int out;     //0~500ms
    int Direction;    //0:input ,1:output;
    double OpenSize;    //0:close ,2.5:half open ,5.0:full open;
    int State_PID;

    double Cerror,Perror,Lerror,Cum_Cerror,abs_Cerror;  //current   before last

};

#endif // MYPID_H
