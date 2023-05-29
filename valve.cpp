#include "valve.h"

Valve::Valve()
{

}

Valve::~Valve()
{

}

void Valve::open_vlave_in(int fd2)
{
    int ret;
#ifdef UBUNTU
    ret = ioctl(fd2,1,0);    //0:valve1  input
//    usleep(20000);
#endif
//    if(ret<0)
//        printf("valve1  input open failed!\n");
//    else
//        printf("valve1  input open success!\n");
}

void Valve::open_vlave_out(int fd2)
{
    int ret;
#ifdef UBUNTU
     ret = ioctl(fd2,1,0);    //1:valve2  output
//     usleep(20000);
#endif
//    if(ret<0)
//        printf("valve2  output open failed!\n");
//    else
//        printf("valve2  output open success!\n");
}

void Valve::close_valve_in(int fd2)
{
    int ret;
#ifdef UBUNTU
    ret = ioctl(fd2,0,0);    //0:valve1  input
//    usleep(20000);
#endif
//    if(ret<0)
//        printf("valve1  input close failed!\n");
//    else
//        printf("valve1  input close success!\n");
}

void Valve::close_vlave_out(int fd2)
{
    int ret;
#ifdef UBUNTU
    ret = ioctl(fd2,0,0);    //1:valve2  output
//    usleep(20000);
#endif
//    if(ret<0)
//        printf("valve2  output close failed!\n");
//    else
//        printf("valve2  output close success!\n");
}
