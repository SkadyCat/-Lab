#include "bluetooth.h"

#include <QtGlobal>

#ifdef Q_OS_LINUX

    #include <unistd.h> /*Unix 标准函数定义*/
    #include <termios.h> /*PPSIX 终端控制定义*/

#endif
#include <stdio.h> /*标准输入输出定义*/
#include <stdlib.h> /*标准函数库定义*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /*文件控制定义*/

#include <errno.h> /*错误号定义*/
#include<QDebug>
#include"writetool.h"

//#include "parser.h"
//#include "serializer.h"
char* BlueTooth::cahce = NULL;
char* BlueTooth::data = NULL;
int BlueTooth::pointer;
BlueTooth* BlueTooth::getInstance(){

    if(Instance == NULL){

        Instance =new BlueTooth();

        BlueTooth::cahce = new char[1024];
        BlueTooth::data = new char[1024];
        return  Instance;
    }

    return Instance;
}

std::function<int(QString*)> BlueTooth::operation = NULL;
int BlueTooth::flag  =0;
BlueTooth::BlueTooth()
{


}
BlueTooth* BlueTooth::Instance = NULL;


void BlueTooth::send(const char* data){


#ifdef Q_OS_LINUX

    int fd = open("/dev/rfcomm0", O_RDWR | O_NOCTTY | O_NDELAY);
    int nByte = 0;
    if (fd < 0)
    return;
    qDebug()<<"open success";
    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE); /*Input*/
    options.c_oflag &= ~OPOST;

    const char*data2  =data;
    nByte = write(fd, data2, strlen(data));
    qDebug()<<nByte;
    close(fd);

#endif
}

int* BlueTooth::Ox2Binary(int vlaue){


    return NULL;
}
void BlueTooth::send(){


#ifdef Q_OS_LINUX

    int fd = open("/dev/rfcomm0", O_RDWR | O_NOCTTY | O_NDELAY);
    int nByte = 0;
    if (fd < 0)
    return;
    qDebug()<<"open success";
    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE); /*Input*/
    options.c_oflag &= ~OPOST;

    char*data2  = "12345";
    nByte = write(fd, data2, 5);
    qDebug()<<nByte;
    close(fd);

#endif

}

QString * BlueTooth::str = NULL;
char* BlueTooth::getData(){


    #ifdef Q_OS_LINUX
    int fd = open("/dev/rfcomm0", O_RDWR | O_NOCTTY | O_NDELAY);
    int nByte = 0;
    if (fd < 0)
    return NULL;

    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); /*Input*/
    options.c_oflag &= ~OPOST; /*Output*/

    int Len = 1;
    int readByte;

//    WriteTool::Instance()->delay_01(1000*10);
    while((readByte = read(fd,BlueTooth::cahce,Len)) > 0){



        switch(BlueTooth::cahce[0]){
            case '<':
                BlueTooth::pointer = 0;
                break;

            case '>':

                 BlueTooth::flag = 1;
                break;

        default:
            BlueTooth::data[BlueTooth::pointer] = BlueTooth::cahce[0];

            BlueTooth::pointer+=1;

            break;
        }
    }
    if(BlueTooth::flag == 1){

        BlueTooth::str = new QString();
        for(int i =0;i<BlueTooth::pointer;i++){
            str->append(data[i]);
        }

        BlueTooth::flag = 0;
        if(operation!= NULL){
           BlueTooth::operation(str);
        }
    }
    close(fd);

    #endif

    return BlueTooth::data;

}
