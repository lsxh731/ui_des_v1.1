#include "myi2c.h"
#include <QDebug>

MyI2C::MyI2C()
{
    adressVin=0x60;
    adressVout=0x61;
}


MyI2C::~MyI2C()
{

}

void MyI2C::i2c_in_WriteData(int fd, double Vin)
{
    unsigned char buffer[2];
    unsigned int tmp;
    int ret;
#ifdef UBUNTU
    tmp  = ( 4096 * Vin) / 5.0;
    buffer[1]  = tmp;                  //low  8 bit
    buffer[0] = (0x0F00 & tmp) >> 8;    //high 4 bit
    ret = write(fd,buffer,2);
    if(ret<0)
        printf("i2c_in_WriteData failed!\n");
    else
        qDebug()<<"i2c_in_WriteData success! in Vin ="<<Vin;
#endif
}

void MyI2C::i2c_out_WriteData(int fd, double Vout)
{
    unsigned char buffer[2];
    unsigned int tmp;
    int ret;
#ifdef UBUNTU
    tmp  = ( 4096 * Vout) / 5.0;
    buffer[1]  = tmp;                  //low  8 bit
    buffer[0] = (0x0F00 & tmp) >> 8;    //high 4 bit
    ret = write(fd,buffer,2);
    if(ret<0)
        printf("i2c_out_WriteData failed!\n");
    else
        qDebug()<<"i2c_out_WriteData success ! out Vout ="<<Vout;
#endif
}
