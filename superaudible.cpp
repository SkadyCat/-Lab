#include "superaudible.h"

#include <QtGlobal>
#include"writetool.h"
#ifdef Q_OS_LINUX
#include"wiringPi.h"
#include "sys/time.h"
#include<QDebug>
#endif

Superaudible* Superaudible::Instance = NULL;



Superaudible::Superaudible()
{

}
int Superaudible::doorCat = 0;
Superaudible::Superaudible(int Trig,int Echo){

#ifdef Q_OS_LINUX
    Instance = this;
    pinMode(Trig, OUTPUT); //设置 Trig 为输出
    pinMode(Echo, INPUT); //设置 Echo 为输入
    digitalWrite(Trig, LOW);
    this->distance = 0;
    this->Trig = Trig;
    this->Echo = Echo;
    this->counter = 0;
#endif

}
 int Superaudible::statu = 0;
void Superaudible::shutDown(){

    statu = 999;
}

void Superaudible::waitLowMessage(){

      Superaudible::Instance ->counter++;
    if(Superaudible::Instance->read(Superaudible::Instance->Echo) == 0){

//        qDebug()<<"counter = "<<Superaudible::Instance ->counter;

//        WriteTool::Instance()->delay_01(1000*1000);
        Superaudible::statu = 3;


    }
    WriteTool::Instance()->delay_01(1);

}

void Superaudible::waitHightMessage(){


    int v = Superaudible::Instance->read(Superaudible::Instance->Echo);
    if(v == 1){//up message get and statu to 2

//        qDebug()<<"counter = "<<Superaudible::Instance ->counter;
         Superaudible::statu = 2;
    }
    WriteTool::Instance()->delay_01(1);

}
int Superaudible::read(int port){

    #ifdef Q_OS_LINUX
        return digitalRead(port);
    #endif


   return 0;
}
void Superaudible::beginSendWave(){
     float dist = -1.;
#ifdef Q_OS_LINUX
     statu = 0;
     digitalWrite(this->Trig, HIGH);
     delayMicroseconds(10); //发送一个 10us 的脉冲
     digitalWrite(Trig, LOW);
     Superaudible::statu = 1;
     Superaudible::Instance ->counter = 0;
     Superaudible::doorCat = 0;
#endif

}

float Superaudible::countDistance(){
    float f2 = this->counter;
    this->distance =(( f2/ 1000000.) * 34000) / 2; //计算距离
    statu = 0;
    this->counter = 0;
    return this->distance;
}
