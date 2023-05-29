#ifndef VALVE_H
#define VALVE_H
#include "commmacro.h"

class Valve
{
public:
    Valve();
    ~Valve();


public:
    void open_vlave_in(int fd2);
    void open_vlave_out(int fd2);
    void close_valve_in(int fd2);
    void close_vlave_out(int fd2);
};

#endif // VALVE_H
