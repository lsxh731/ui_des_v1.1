#include "pwmqthread.h"
#include <stdint.h>

extern int ifq;

extern USEPOSI Useposi;
extern SETPOSI Setpposi;


PwmqThread::PwmqThread(QObject *parent) : QObject(parent)
{
    this->Device_init();
    ToStop = false;
    AorM = true;
    posi = 0;
    pres = 0;
    OutCount = 0;
    InCount = 0;
    Sum_posi = 0;
    v_posi = 0;
    posi_1 = 0;
    posi_2 = 0;
    posi_3 = 0;
    posi_4 = 0;

    memset(ad_bf,0,sizeof (ad_bf));
    Ave_posi = 27.6;

    Height = 110;
    Width = 28;
    HalfRange = 53.5;

    OutCtlfreq = 5;
    InCtlfreq = 5;
    CutOffreq = 1;
    InChange = 1000.0;
    OutChange = 1000.0;
    CtlAccu = 1.0;
    EctlRatio = 50;
    OutV = 0.0;

    a = CutOffreq*2*PI*0.000125;

    countEmg = 80;
    isOKtoEMG = false;
    QavePosi.clear();
    Qqyn1.clear();

    pcont=0;
    this->RS485_SetRange();
}

void PwmqThread::Manu_PWM()
{
    qDebug()<<"#####thread####";
    Ave_posi = 0;
    if(ToStop)
        return;
    while(!ToStop)
    {
#ifdef UBUNTU
        /********************实际使用程序 ***************************************/
            usleep(115);//OFF time  1k=800/200   2k=400/100   8k=100/25   == usleep(Ioff);
            ioctl(fd_MyPwm1,1,0);
            usleep(10);//ON time  == usleep(Ion);
            this->Ad7606_HighRead();
            ioctl(fd_MyPwm1,0,0);
#endif
    }
}

void PwmqThread::Ad7606_HighRead()
{
    read(fd_AdSpi,ad_bf,6);
    posi = ((( ad_bf[1])<<8)+ad_bf[2])*5.0/32768;
    pres = ((( ad_bf[3])<<8)+ad_bf[4])*5.0/32768;
    v_posi = posi;
    if(posi > 5.0) posi = posi_1;
    posi = (posi+posi_1+posi_2+posi_3+posi_4)/5.0;
    posi_4= posi_3;
    posi_3= posi_2;
    posi_2= posi_1;
    posi_1 = posi;
    /*松下HG-C1050*/
    posi = 30 - 6*posi;         //y=k*x+b,(x1,0),(x2,27),k=27/(x2-x1),b=27*x1/(x2-x1)  近段x1，远端x2
    posi = posi*Height/Width;  //近段 偏高 + 放气  、、、  远端 偏低 - 进气   最高点为0mm
    //一阶滤波
    Yn = a*posi+(1.0-a)*Yn_1;
    Yn_1 = Yn;
    //二阶滤波
    Yn1 = a*Yn+(1.0-a)*Yn1_1;
    Yn1_1 = Yn1;

    OutCount++;
    InCount++;
    /*新版程序start*/
    if(Qqyn1.size()>8000){
        Sum_posi = Sum_posi-Qqyn1.first();
        Qqyn1.pop_front();
    }
    Qqyn1.push_back(Yn1);
    Sum_posi+=Yn1;
    /*新版程序end*/
#if 0
    if(OutCount > int(8000/OutCtlfreq))  //OUT freq
    {
        Ave_posi = Sum_posi/Qqyn1.size();
        OutCount = 0;
        emit start_pid();
    }
#endif
    if(OutCount > int(8000/Useposi.OutCtlfreq))  //OUT freq
    {
        Ave_posi = Sum_posi/Qqyn1.size();
        OutCount = 0;
        if((target-Ave_posi) >= 0 )
            emit start_pid();
    }
    if(InCount > int(8000/Useposi.InCtlfreq))   //IN freq
    {
        Ave_posi = Sum_posi/Qqyn1.size();
        InCount = 0;
        if((target-Ave_posi) < 0 )
            emit start_pid();
    }
}
void PwmqThread::Ad7606_LowRead()
{
    read(fd_AdSpi,ad_bf,6);
    posi = ((( ad_bf[1])<<8)+ad_bf[2])*5.0/32768;
    pres = ((( ad_bf[3])<<8)+ad_bf[4])*5.0/32768;
    if(posi > 5.0) posi = posi -5.0;
    Ave_posi = (30-6*posi)*Height/Width;
#ifdef UBUNTU
    if(Ave_posi > 117)
        ioctl(fd_AdSpi,10,10);
#endif
    pcont++;
    if(pcont%4 == 0)
    {
        pcont=0;
//        RS485SendData(Ave_posi);  //send ave-posi
//        RS485_SetRange();
    }

}


void PwmqThread::Device_init()
{
#ifdef UBUNTU

    MyWidgetHandle = new mywidget;
    /*****************AD7606_SPI Open*********************************/
    char *adspi_node = "/dev/adspi";
    if((fd_AdSpi = open(adspi_node, O_RDWR))<0)
    {
        qDebug()<<"AD7606_SPI Open %s failed!";
//        return;
    }
    else
    {
        printf("AD7606_SPI Open success!\n");
    }
    int ret;

    static uint8_t mode = SPI_MODE_3;
//    static uint8_t mode = SPI_MODE_0;
    ret = ioctl(fd_AdSpi, SPI_IOC_WR_MODE, &mode);
    if (ret == -1)
        printf("can't set spi mode");

    ret = ioctl(fd_AdSpi, SPI_IOC_RD_MODE, &mode);
    if (ret == -1)
        printf("can't get spi mode");

    static uint8_t bits = 8;
    ret = ioctl(fd_AdSpi, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1)
        printf("can't set bits per word\n");

    ret = ioctl(fd_AdSpi, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1)
        printf("can't get bits per word\n");

    static uint32_t speed = 10*1000*1000;//10M;
    ret = ioctl(fd_AdSpi, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        printf("can't set max speed hz\n");

    ret = ioctl(fd_AdSpi, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1)
        printf("can't get max speed hz\n");

    printf("spi mode: %d\n", mode);
    printf("bits per word: %d\n", bits);
    printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

    /*****************MyPWM1 Open*********************************/
    char *mypwm_node = "/dev/myhrtimer";
    if((fd_MyPwm1 = open(mypwm_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
    {
         qDebug()<<"MyPWM Open  failed!";
//         return;
    }
    else
    {
         printf("MyPWM Open success!\n");
    }
    //add by zw for 485


    /*****************ttySAC1 for 485 Open*********************************/
    char *ttySAC1_node = "/dev/ttySAC1";
    if((fd_ttySAC1 = open(ttySAC1_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
    {
         qDebug()<<"ttySAC1 Open  failed!";
//         return;
    }
    else
    {
         printf("ttySAC1 Open success!\n");
         set_opt(fd_ttySAC1, 9600, 8, 'N', 1);
    }
    /*****************ctl pin for 485 Open*********************************/
    char *rs485ctlpin_node = "/dev/rs485ctl";
    if((fd_485ctlp = open(rs485ctlpin_node, O_RDWR|O_NOCTTY|O_NDELAY))<0)
    {
         qDebug()<<"rs485ctl Open  failed!";
//         return;
    }
    else
    {
         printf("rs485ctl Open success!\n");
    }

#endif
}

void PwmqThread::dataHighGet(double dposi)
{
    if(isOKtoEMG)
    {
        if(abs(dposi - p_avposi) > 3.0)
        {
            isOKtoEMG = false;
            countEmg = 40;
//            qDebug()<<"#####An emergency has arisen #####";
            QString strtime;
            QDateTime current_date_time =QDateTime::currentDateTime();
            strtime =current_date_time.toUTC().toString("yyyy-MM-dd-hh-mm");
            QString str_name = QString("./log/emgfile-%1.txt").arg(strtime);
            QString print = QString("TIME:%1 Sample Rate:8 kHz Sample Time: 1 second \n").arg(strtime);
            QFile Log_date(str_name);
            if(Log_date.open(QFile::WriteOnly|QIODevice::Truncate))
            {
                Log_date.write(print.toUtf8());
                for(int i=0;i<QavePosi.size();i++)
                {
                    QString strdata = QString("%1\n").arg(QavePosi[i]);
                    Log_date.write(strdata.toUtf8());
                }
                Log_date.write("\n");
                Log_date.close();
            }
        }
    }
    p_avposi = dposi;
}

//add by zw for 485
/* 5Hz send rate
 * char recv_buffer[4];
 * float recv_float;
 * read(fd_ttySAC1,recv_buffer,sizeof(recv_buffer));
 * recv_float=*(float*)&recv_buffer[0];
 * printf("recv_float = %f\n",recv_float);
*/
void PwmqThread::RS485SendData(double send)
{
#ifdef UBUNTU
    int ret;
    float fTmp;
    char *bf;
//    fTmp = (Zero_p - (float)Ave_posi);
    fTmp = (float)(target-send);
//    fTmp = 50.1;
    bf = (char*)&fTmp;
    ret = ioctl(fd_485ctlp,1,0);
    write(fd_ttySAC1,bf,sizeof(bf));
//    usleep(2*(8*sizeof(bf)+2)*100);   //100=1000000/B9600
#endif
}
//add end

unsigned int PwmqThread::crc_chk(unsigned char *data,unsigned char length)
{
    int i,j;
    unsigned int crc_reg =0xffff;
    while(length--)
    {
      crc_reg^=*data++;
      for(j=0;j<8;j++)
      {
      if(crc_reg&0x01)
       {
        crc_reg=(crc_reg>>1)^0xa001;
       }
       else
       {
       crc_reg=crc_reg>>1;
       }
      }
    }
    return crc_reg;
}

void PwmqThread::RS485_SetVoltage(float v)
{
    int ret;
    unsigned char bf[11]={0x01,0x10,0x00,0x00,0x00,0x01,0x02,0x00,0x00,0x00,0x00};
    unsigned int crc_reg;
    unsigned int tmp_v;
    v = -Useposi.VOutMax*v/50.0;
    if(v > Useposi.VOutMax) v=Useposi.VOutMax;
    if(v < -1*Useposi.VOutMax) v=-1*Useposi.VOutMax;
    Useposi.vOut = v*Setpposi.EctlRatio/100;
    tmp_v = ((VCOE*Useposi.vOut+10)/20)*4095;
    bf[7]=(tmp_v>>8)&0xff;
    bf[8]=tmp_v&0xff;
    crc_reg = crc_chk(bf,(sizeof (bf)-2));
    bf[9]=crc_reg&0xff;
    bf[10]=(crc_reg>>8)&0xff;
#ifdef UBUNTU
    ret = ioctl(fd_485ctlp,1,0);
    write(fd_ttySAC1,bf,sizeof(bf));
    usleep(2*(8*sizeof(bf)+2)*100);//100=1000000/B9600
#endif
}

void PwmqThread::RS485_SetPidVoltage(float v)
{
    int ret;
    unsigned char bf[11]={0x01,0x10,0x00,0x00,0x00,0x01,0x02,0x00,0x00,0x00,0x00};
    unsigned int crc_reg;
    unsigned int tmp_v;
    OutV += v;
    if(OutV >Useposi.VOutMax ) OutV=Useposi.VOutMax;
    if(OutV < -1*Useposi.VOutMax) OutV=-1*Useposi.VOutMax;
    Useposi.vOut = OutV*Setpposi.EctlRatio/100;
    tmp_v = ((VCOE*Useposi.vOut+10)/20)*4095;
    bf[7]=(tmp_v>>8)&0xff;
    bf[8]=tmp_v&0xff;
    crc_reg = crc_chk(bf,(sizeof (bf)-2));
    bf[9]=crc_reg&0xff;
    bf[10]=(crc_reg>>8)&0xff;
#ifdef UBUNTU
    ret = ioctl(fd_485ctlp,1,0);
    write(fd_ttySAC1,bf,sizeof(bf));
    usleep(2*(8*sizeof(bf)+2)*100);//100=1000000/B9600
#endif
}

void PwmqThread::RS485_SetRange()
{
    int ret;
    unsigned char bf01[11]={0x01,0x10,0x02,0x00,0x00,0x01,0x02,0x00,0x32,0x04,0x45};// -10v--10v
    unsigned char bf02[11]={0x01,0x10,0x02,0x30,0x00,0x01,0x02,0x07,0xff,0xc2,0x10};// 上电默认输出值：0v
    unsigned char bf03[11]={0x01,0x10,0x02,0x34,0x00,0x01,0x02,0x07,0xff,0xc3,0x94};// 通讯超时默认输出值0v
#ifdef UBUNTU
    ret = ioctl(fd_485ctlp,1,0);
    write(fd_ttySAC1,bf01,sizeof(bf01));
    usleep(2*(8*sizeof(bf01)+2)*100);//100=1000000/B9600

    ret = ioctl(fd_485ctlp,1,0);
    write(fd_ttySAC1,bf02,sizeof(bf02));
    usleep(2*(8*sizeof(bf02)+2)*100);//100=1000000/B9600

    ret = ioctl(fd_485ctlp,1,0);
    write(fd_ttySAC1,bf03,sizeof(bf03));
    usleep(2*(8*sizeof(bf03)+2)*100);//100=1000000/B9600
#endif
}

int PwmqThread::set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
#ifdef UBUNTU
    struct termios newtio,oldtio;
    if  ( tcgetattr( fd,&oldtio)  !=  0) {
        perror("SetupSerial 1");
        return -1;
    }
    bzero( &newtio, sizeof( newtio ) );
    newtio.c_cflag  |=  CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch( nBits )
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch( nEvent )
    {
    case 'O':
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }

    switch( nSpeed )
    {
    case 1200:
        cfsetispeed(&newtio, B1200);
        cfsetospeed(&newtio, B1200);
        break;
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    case 460800:
        cfsetispeed(&newtio, B460800);
        cfsetospeed(&newtio, B460800);
        break;
    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }
    if( nStop == 1 )
        newtio.c_cflag &=  ~CSTOPB;
    else if ( nStop == 2 )
    newtio.c_cflag |=  CSTOPB;
    newtio.c_cc[VTIME]  = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("com set error");
        return -1;
    }
    return 0;
#endif
}



