#ifndef SERIAL_H
#define SERIAL_H
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

using namespace std;
#define COM_NAME "/dev/ttyUSB0"
class comconfigure{
public:
    int set_opt(int fd,int comspeed,int comBits,char comEvent,int comStop);
};
#endif // SERIAL_H
