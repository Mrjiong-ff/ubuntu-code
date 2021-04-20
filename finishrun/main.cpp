#include<color.h>
//#include<findball.h>
//#include<goback.h>
#include<serial.h>
#include<time.h>
int main(){
    Mat frame;
    comconfigure com;
    colorknow know;
    int fd,result=0;
    int nm;
    struct termios options;
    fd = open(COM_NAME, O_RDWR | O_NOCTTY |O_NDELAY);
    int q;
    char rq[512]={"0"};
    char buff;
    char auff;
    char buffer[512];
    char len;
    memset(buffer,0,sizeof(buffer));
    com.set_opt(fd,115200,8,'N',1);
    buff  = 'b';
    auff  = 'a';
    nm = 1;
    while (1)
    {
    read(fd,rq,512);
    rq[0]+=96;
    rq[nm]='\0';
    if(rq[0]=='b'){
    result=know.color();
    }
    if(result==1){
        cout<<"qnmd"<<endl;
        for (int i=0;i<1;i++) {
            write(fd,&buff,8);
        }
    }
    char(key) = (char)waitKey(1);
    if(key == 27){
    break;
    }
     }
    return 0;
}
