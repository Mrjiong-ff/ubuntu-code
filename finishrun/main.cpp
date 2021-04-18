#include<color.h>
//#include<findball.h>
//#include<goback.h>
#include<serial.h>
#include<time.h>
int main(){
    Mat frame;
    comconfigure com;
//    back come;
//    finding ball;
    colorknow know;
    int fd,result;
    int nm;
    struct termios options;
    fd = open(COM_NAME, O_RDWR | O_NOCTTY |O_NDELAY);
//    fd = open("dev/ttyUSB0", O_RDWR | O_NOCTTY |O_NDELAY);
    int q;
    char rq[512]={"0"};
    unsigned char buff;
    char buffer[512];
    char len;
//    while(read(fd,rw,10) != -1){
    memset(buffer,0,sizeof(buffer));
    com.set_opt(fd,115200,8,'N',1);
//    while(read(fd,rq,1) > 0){
//        ball.findball();
    buff  = 'g ';
    nm = 1;
    while (1) {
    read(fd,rq,512);
    rq[0]+=96;
    rq[nm]='\0';
//          write(fd,buff,sizeof(buffer));
//    if(rq[0]=='b')
    know.color();
//    rq=rq+96;
//    cout<<rq<<endl;
//        nm=sizeof(fd);
//        write(fd,&buff,1);
//    }

    return 0;
    }
    }
