#include "sx.h"
#include <Qt>
#include "ui_mainwindow.h"

#include "mainwindow.h"
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QMessageBox>
#include<QToolBar>
#include <QCloseEvent>

Sx* Sx::ins = NULL;
int Sx::closeStatu = 0;
Sx::Sx()
{
   ins = this;
    this->mainCode = 0;
    this->subCode = 0;
   this->portPointer = 0;
   this->timeCounter = 0;
   closeStatu = 100;
}
void Sx::setCode(int mainCode, int subCode){

    this->mainCode = mainCode;
    this->subCode = subCode;
}
void Sx::mousePressEvent(QMouseEvent *event){

    emit this->clickEvent_001();


}
std::string Sx::toStdStr(QString val){


    return val.toStdString();

}
void Sx::trigger0001(){

    debug("trigger");
    //**
    debug("??");

}
void Sx::clickEvent_001Process(){




}
// 重写closeEvent: 确认退出对话框
void Sx::closeEvent(QCloseEvent *event)
{

    closeStatu = 999;
    threadSir->quit();
    QMessageBox::StandardButton button;
    button=QMessageBox::question(this,"exit",QString("please confirm"),QMessageBox::Yes|QMessageBox::No);
    if(button==QMessageBox::No)
    {
        event->ignore(); // 忽略退出信号，程序继续进行
    }
    else if(button==QMessageBox::Yes)
    {
        event->accept(); // 接受退出信号，程序退出
    }
}
void Sx::btn_0001Process(){

    debug("who click?");
}
void Sx::setConsole(const char *value){

    this->consoleLabel->setText(value);

}
void Sx::debug(const char *value){

     QMessageBox::information(this,"Info",value,QMessageBox::Ok);
}
void Sx::timerUpDate(){
    static int time = 0;
    QString qs ="now time = "+ QString::number(time);


    this->label->setText(qs);
    time++;

}
Sx::~Sx()
{



}
Sx* Sx::Instance(){


       return ins;
}
//void Sx::closeEvent (){

//    debug("shut down");
//    closeStatu = 999;
//    threadSir->quit();


//}
