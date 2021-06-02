#include "writetool.h"
 #include "sx.h"
#include <QtGlobal>

#ifdef Q_OS_LINUX

#include"wiringPi.h"

#endif

WriteTool* WriteTool::ins;

WriteTool::WriteTool()
{
    ins = this;
#ifdef Q_OS_LINUX

  wiringPiSetup();

#endif

#ifdef Q_OS_WIN32
// win


#endif

}

WriteTool* WriteTool::Instance(){

    return ins;
}

void WriteTool::setMode(int port, int value){
#ifdef Q_OS_LINUX

    pinMode(port,value);

#endif
#ifdef Q_OS_WIN32
// win
//    Sx::Instance()->consoLabel.setText("正在使用PinMode命令");
#endif
}

void WriteTool::setGPIO(int port, int value){

#ifdef Q_OS_LINUX

    digitalWrite(port,value);

#endif
}

void WriteTool::delay_01(int value){

#ifdef Q_OS_LINUX

    delayMicroseconds(value);

#endif
}

int WriteTool::getGPIO(int port){

#ifdef Q_OS_LINUX

    return digitalRead(port);

#endif
    return 0;
}
