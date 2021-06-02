#include "interrupt.h"
#include"writetool.h"
#include<QtGlobal>

#include<QDebug>
#ifdef Q_OS_LINUX

#include"wiringPi.h"

#endif
#include"writetool.h"
Interrupt::Interrupt()
{

}

void Interrupt::initInterrupt(){


}
int Interrupt::pointer = 0;
Interrupt* Interrupt::arr = new Interrupt[40];

Interrupt::Interrupt(int gpioPort,std::function<int()> operation){
    this->gpioPort = gpioPort;
    initKey(gpioPort);

    Interrupt::arr[gpioPort] = *this;
    Interrupt::workGpioPort[gpioPort] = gpioPort;
    this->setFunc(operation);
    WriteTool::Instance()->setMode(gpioPort,INPUT);

}
Interrupt::Interrupt(int gpioPort){


    this->gpioPort = gpioPort;
    initKey(gpioPort);

    Interrupt::arr[gpioPort] = *this;
    Interrupt::workGpioPort[gpioPort] = gpioPort;

}
void Interrupt::setFunc(std::function<int ()> operation){

    qDebug()<<"init the index"<<Interrupt::arr[gpioPort].gpioPort;
    Interrupt::arr[gpioPort].f = operation;
}


int* Interrupt::workGpioPort = NULL;
int Interrupt::workGpioNum = 0;
void ops(){


    for(int i =0;i<Interrupt::workGpioNum;i++){

        if(Interrupt::workGpioPort[i]== -1){

            continue;
        }
        WriteTool::Instance()->delay_01(1000*50);//延迟1000*50
        if(WriteTool::Instance()->getGPIO(Interrupt::workGpioPort[i]) == 0){
            Interrupt::arr[Interrupt::workGpioPort[i]].f();
        }
    }
}
void Interrupt::initKey(int gpioPort){


    #ifdef Q_OS_LINUX

    pinMode(gpioPort, INPUT);
    pullUpDnControl(gpioPort, PUD_UP); //设置上拉电阻

    //注册中断程序

    wiringPiISR(gpioPort, INT_EDGE_FALLING, &ops);
    #endif




}


