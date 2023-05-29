#ifndef MYI2C_H
#define MYI2C_H

class MyI2C
{
public:
    MyI2C();
    ~MyI2C();

    unsigned char adressVin;
    unsigned char adressVout;
    void i2c_in_WriteData(int fd,double Vin);
    void i2c_out_WriteData(int fd,double Vout);
};

#endif // MYI2C_H
