#include "dtcontroller.h"

#include <QtGlobal>
#include"writetool.h"
#ifdef Q_OS_LINUX

#include"wiringPi.h"

#endif

int DTController::pointerIndex = 0;
unsigned char DTController::data[]
{
    0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80,
    0x90, 0x8c, 0xbf, 0xc6, 0xa1, 0x8e, 0xbf, 0xff, 0x7f, 0xbf
};
unsigned char DTController::path[] = {
  0x08,0x04,0x02,0x01
};

int* DTController::Ox2Binary(int value){


    int a = value;
    int b = 0x80;
    int* vi = new int[8];
    for (int i = 0; i < 8; i++) {

        vi[7 - i] = ((a) % 2);
        a = a >> 1;
    }
    return vi;
}
void DTController::DTWrite(int SCLK,int DIO,int value){
    int* vl = DTController::Ox2Binary(value);
    #ifdef Q_OS_LINUX


    for(int i =0;i<8;i++) //循环 8 次为 1 字节
    {
           digitalWrite(DIO,vl[i]);
           delayMicroseconds(1);
           digitalWrite(SCLK,LOW);
           delayMicroseconds(1);
           digitalWrite(SCLK,HIGH);
           delayMicroseconds(1);
    }

    #endif

}

void DTController::Bright(int SCLK,int RCLK,int DIO,int path, int value){

    WriteTool::Instance()->setMode(SCLK,OUTPUT);
    WriteTool::Instance()->setMode(RCLK,OUTPUT);
    WriteTool::Instance()->setMode(DIO,OUTPUT);
    DTWrite(SCLK,DIO,DTController::data[value]);
    DTWrite(SCLK,DIO,DTController::path[path]);
    #ifdef Q_OS_LINUX
        digitalWrite(RCLK,0); //在 RCLK 上输出脉冲信号
        delayMicroseconds(1);
        digitalWrite(RCLK,1);
        delayMicroseconds(10);
    #endif
}

void DTController::BrightAll(int SCLK,int RCLK,int DIO,int showData[],int * index){

    if(showData == NULL)
        return;

    Bright(SCLK,RCLK,DIO,*index%4,showData[*index%4]);
    *index+=1;

    if(*index==64){
        index = 0;
    }
}
DTController::DTController()
{

}
