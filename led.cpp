#include "led.h"
#include"writetool.h"
LED::LED()
{

    Instance = this;
}

LED* LED::Instance ;

LED* LED::getInstance(){

    for(int i =0;i<8;i++){

        WriteTool::Instance()->setMode(i,OUTPUT);

    }
    return Instance;
}

void LED::brightAll()
{
    for(int i =0;i<8;i++){

        WriteTool::Instance()->setGPIO(i,LOW);
    }
}

void LED::extinguishAll(){

    for(int i =0;i<8;i++){



        WriteTool::Instance()->setGPIO(i,HIGH);
    }
}

void LED::brightSingle(int index){


    WriteTool::Instance()->setGPIO(index,LOW);
}

void LED::extinguishSingle(int index){



    WriteTool::Instance()->setGPIO(index,HIGH);
}
