#include "pcf.h"
#include <QtGlobal>
#include"writetool.h"
#ifdef Q_OS_LINUX

#include"wiringPi.h"
#include "wiringPiI2C.h"
#endif
int PCF::address = 0x48;

int PCF::path[] = {0x40,0x41,0x42,0x43};
int PCF::data[] = {0,0,0,0};
int PCF::fd = 0;
int PCF::pointer = 0;
void PCF::init(){
    #ifdef Q_OS_LINUX
        fd = wiringPiI2CSetup(address); //初始化 I2C
    #endif
}
int PCF_read(int channel)
{
     int value;
    #ifdef Q_OS_LINUX

    wiringPiI2CWriteReg8(PCF::fd, PCF::path[channel], 1); //写入任意一个数据，开启该通道的采集
    delay(1);
    value = wiringPiI2CReadReg8(PCF::fd, PCF::path[channel]); //读取数据

    #endif
    return value;
}
void PCF::toIntArr(int *container, int value){

    for(int i =0;i<4;i++){
        container[3-i] = value%10;
        value = value/10;
    }


}
int PCF::read(){

    int value = 0;
    #ifdef Q_OS_LINUX

    data[pointer%4] = PCF_read(pointer%4);

    value = data[pointer%4];
    #endif

       pointer++;
       return value;
}
PCF::PCF()
{


}
