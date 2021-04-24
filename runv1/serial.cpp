#include<serial.h>
int comconfigure::set_opt(int fd,int comspeed,int comBits,char comEvent,int comStop){
    struct termios newtio,oldtio;
    if( tcgetattr(fd,&oldtio) !=0){
       perror("SetupSerial 1");
       return -1;
    }
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch(comBits){
    case 7:
        newtio.c_cflag |= CS8;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch (comEvent) {
    case 'N':
        newtio.c_cflag &= PARENB;
        break;
    }
    switch (comspeed) {
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    default:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    }
    if(comStop == 1){
        newtio.c_cflag &= ~CSTOPB;
        newtio.c_cc[VTIME] = 5;
        newtio.c_cc[VMIN] = 0;

//        newtio.c_cflag &= ~HUPCL;
//        newtio.c_iflag &= ~INPCK;
//        newtio.c_iflag |= IGNBRK;
//        newtio.c_iflag &= ~ICRNL;
//        newtio.c_iflag &= ~IXON;
//        newtio.c_iflag &= ~IEXTEN;
//        newtio.c_iflag &= ~ECHOK;
//        newtio.c_iflag &= ~ECHOCTL;
//        newtio.c_iflag &= ~ECHOKE;
//        newtio.c_oflag &= ~ONLCR;

        tcflush(fd,TCIFLUSH);
    }
    if((tcsetattr(fd,TCSANOW,&newtio))!=0){
        perror("comset error");
        return -1;
    }else{
        cout<<"set done!"<<endl;
    }
    return 0;
}
