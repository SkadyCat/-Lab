#include "processer.h"
#include    "sx.h"
#include<QLabel>
#include"writetool.h"

#include"bluetooth.h"
#include"dtcontroller.h"
#include"pcf.h"
#include <QDebug>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include    "interrupt.h"
#include"superaudible.h"
#include "bme280.h"
#include"led.h"
#include"camerase.h"
#include"fileviewwidget.h"
#include<QImage>
#include"facesir.h"
#include"calculator.h"
#include"gamewindow.h"
#include"mp3.h"
//---task_2 cahce---//
int* data1;
int* data2;
int data1Index = 0;
int data2Index = 0;

int task_2_v1 = 0;
int task_2_v2 = 0;
QLineEdit *task_2_v3;
//---task_3 cahce---//

int task_3_v1 = 0;
int task_3_v2 = 20;
int task_3_v1_flag = 0;
//---task_4 cahce---//
int task_4_v1 = 0;

//---task_6 chache//
float task_6_v1 = 0;//TEMPERATURE
float task_6_v2 = 0;//humidity
float task_6_v3 = 0;//pressure


//---task_6 chache//
float task_7_v1 = 0;//TEMPERATURE

//int PCF_read(int channel)
//{
//    int value;
//    wiringPiI2CWriteReg8(PCF::fd, channel, 1); //写入任意一个数据，开启该通道的采集
//    delay(1);
//    value = wiringPiI2CReadReg8(PCF::fd, channel); //读取数据
//    return value;
//}
Processer* Processer::Instance= NULL;
Processer::Processer(QWidget *pt):
     QLabel(pt)
{

}
Processer::Processer()
{
    Instance = this;

    data1 = new int[4]{1,2,3,4};
    data2 = new int[4]{1,2,3,4};
}
void Processer:: BrightAll(){
    for(int i =0;i<8;i++){

        WriteTool::Instance()->setMode(i,OUTPUT);
        WriteTool::Instance()->setGPIO(i,LOW);

    }

}
void Processer:: ExtinguishAll(){

    for(int i =0;i<8;i++){

        WriteTool::Instance()->setMode(i,OUTPUT);

        WriteTool::Instance()->setGPIO(i,HIGH);
    }
}


static int counter = 0;
/**
 * @brief Processer::threadEvent
 *
 * thread event and dont use any ui thread function under it
 * @param mainCode
 * @param subCode
 */
void Processer::threadEvent(int mainCode, int subCode){




    if(mainCode == 2){

        if(subCode == 1){

            int a = 357;


             DTController::BrightAll(0,1,2,data1,&data1Index);
        }

        if(subCode == 2){

                PCF::toIntArr(data1,PCF::data[0]);
                PCF::toIntArr(data2,PCF::data[3]);
                DTController::BrightAll(0,1,2,data1,&data1Index);
                DTController::BrightAll(3,4,5,data2,&data2Index);

        }

        if(subCode == 3){

            PCF::toIntArr(data1,task_2_v1);
            PCF::toIntArr(data2,task_2_v2);
            DTController::BrightAll(0,1,2,data1,&data1Index);
            DTController::BrightAll(3,4,5,data2,&data2Index);
        }
    }


    if(mainCode == 3){

        if(subCode== 1 )

        {

            PCF::toIntArr(data1,task_3_v1);
            PCF::toIntArr(data2,task_3_v2);
            DTController::BrightAll(0,1,2,data1,&data1Index);
            DTController::BrightAll(6,7,21,data2,&data2Index);
        }
    }
    if(mainCode == 4){

        if(subCode== 1 )
        {

            if(Superaudible::statu == 0){

                  Superaudible::Instance->beginSendWave();

            }

            if(Superaudible::statu == 1){



                Superaudible::Instance->waitHightMessage();

            }
            if(Superaudible::statu == 2){


                Superaudible::Instance->waitLowMessage();


            }
            if(Superaudible::statu == 3){

                task_4_v1 = Superaudible::Instance->countDistance();

                WriteTool::Instance()->delay_01(1000*100);
            }
        }
    }


    if(mainCode == 6){
        if(subCode == 1){
            PCF::toIntArr(data1,task_6_v1);
            PCF::toIntArr(data2,task_6_v2);
            DTController::BrightAll(0,1,2,data1,&data1Index);
            DTController::BrightAll(6,7,21,data2,&data2Index);
        }

    }

    if(mainCode == 7){

        if(subCode == 2){

            BlueTooth::getInstance()->getData();

        }
    }
}




void Processer::updateProcess(){

    int mainCode = Sx::Instance()->mainCode;
    int subCode = Sx::Instance()->subCode;


    if(mainCode == 1){

        if(subCode == 3){


                        if(Sx::Instance()->timeCounter%8 == 0){

                            ExtinguishAll();
                            WriteTool::Instance()->setMode(Sx::Instance()->timeCounter%8,OUTPUT);
                            WriteTool::Instance()->setGPIO(Sx::Instance()->timeCounter%8,LOW);
                            Sx::Instance()->consoleLabel->setText(
                                        "now the bright numer is "+
                                        QString::number(Sx::Instance()->timeCounter%8)+
                                        "\nthe count time is "+QString::number(Sx::Instance()->timeCounter));
                            Sx::Instance()->timeCounter++;
                            return;
                        }

                        WriteTool::Instance()->setMode(Sx::Instance()->timeCounter%8,OUTPUT);
                        WriteTool::Instance()->setGPIO(Sx::Instance()->timeCounter%8,LOW);
                        Sx::Instance()->consoleLabel->setText(
                                    "now the bright numer is "+
                                    QString::number(Sx::Instance()->timeCounter%8)+
                                    "\nthe count time is "+QString::number(Sx::Instance()->timeCounter));
                        Sx::Instance()->timeCounter++;


        }

        if(subCode == 4){
            int numer = 7 - Sx::Instance()->timeCounter%8;
            if(Sx::Instance()->timeCounter%8 == 0){

                ExtinguishAll();

                WriteTool::Instance()->setMode(numer,OUTPUT);
                WriteTool::Instance()->setGPIO(numer,LOW);
                Sx::Instance()->consoleLabel->setText(
                            "reverse time counter show led statu:\n now the bright numer is " +
                            QString::number(Sx::Instance()->timeCounter%8)+
                            "\nthe count time is "+QString::number(Sx::Instance()->timeCounter));
                Sx::Instance()->timeCounter++;
                return;
            }

            WriteTool::Instance()->setMode(numer,OUTPUT);
            WriteTool::Instance()->setGPIO(numer,LOW);
            Sx::Instance()->consoleLabel->setText(
                        "reverse time counter show led statu:\n now the bright numer is " +
                        QString::number(Sx::Instance()->timeCounter%8)+
                        "\nthe count time is "+QString::number(Sx::Instance()->timeCounter));
            Sx::Instance()->timeCounter++;

        }
        if(subCode ==5){
            int numer = 3 - Sx::Instance()->timeCounter%4;
            int numer2 = 4+ Sx::Instance()->timeCounter%4;
            if(Sx::Instance()->timeCounter%4 == 0){

                ExtinguishAll();

                WriteTool::Instance()->setMode(numer,OUTPUT);
                WriteTool::Instance()->setGPIO(numer,LOW);
                WriteTool::Instance()->setMode(numer2,OUTPUT);
                WriteTool::Instance()->setGPIO(numer2,LOW);

                Sx::Instance()->consoleLabel->setText(
                            "reverse time counter show led statu:\n now the bright numer is " +
                            QString::number(numer)+
                            " and "+QString::number(numer2)+
                            "\nthe count time is "+QString::number(Sx::Instance()->timeCounter));
                Sx::Instance()->timeCounter++;
                return;
            }

            WriteTool::Instance()->setMode(numer,OUTPUT);
            WriteTool::Instance()->setGPIO(numer,LOW);
            WriteTool::Instance()->setMode(numer2,OUTPUT);
            WriteTool::Instance()->setGPIO(numer2,LOW);
            Sx::Instance()->consoleLabel->setText(
                        "reverse time counter show led statu:\n now the bright numer is " +
                        QString::number(numer)+
                        "and "+QString::number(numer2)+
                        "\nthe count time is "+QString::number(Sx::Instance()->timeCounter));
            Sx::Instance()->timeCounter++;

        }

    }

    if(mainCode == 2){

        if(subCode == 1){

            Sx::Instance()->setConsole(QString::number(counter).toStdString().c_str());




        }

        if(subCode == 2){

            std::string val = "";
            val+= "[Counter]:" +QString::number(counter).toStdString()+"\n";
            val+= "[Temperature]:" +QString::number(PCF::data[2]).toStdString()+"\n";
            val+= "[Light]:" +QString::number(PCF::data[3]).toStdString()+"\n";
            val+= "[Changeable]:" +QString::number(PCF::data[0]).toStdString()+"\n";
            Sx::Instance()->setConsole(val.c_str());
            int values = PCF::read();

        }


    }


    if(mainCode == 4){
        if(subCode == 1){

            PCF::toIntArr(data1,task_4_v1);
            PCF::toIntArr(data2,task_4_v1);
            DTController::BrightAll(0,1,2,data1,&data1Index);
            DTController::BrightAll(6,7,21,data2,&data2Index);
            Superaudible::doorCat++;
            std::string v2 = "";
            v2+="statu = "+QString::number(Superaudible::statu).toStdString()+"\n";
            v2+="distance = "+QString::number(task_4_v1).toStdString()+"\n";
            v2+="watchdog = "+QString::number(Superaudible::doorCat).toStdString();
            Sx::Instance()->setConsole(v2.c_str());


            if(Superaudible::doorCat>2000){

                Superaudible::Instance->beginSendWave();
            }

        }

    }

    if(mainCode == 6){
        if(subCode == 1){

            task_6_v1 = BME280::Instance->getTemperature();
            task_6_v2 =  BME280::Instance->getHumidity();
            task_6_v3 =  BME280::Instance->getPressure();
            std::string v2 = "";
            v2+="Temperature = "+QString::number(task_6_v1).toStdString()+"\n";
            v2+="Humidity = "+QString::number(task_6_v2).toStdString()+"\n";
            v2+="Pressure = "+QString::number(task_6_v3).toStdString();
            Sx::Instance()->setConsole(v2.c_str());
        }
    }

    if(mainCode == 7){
        if(subCode == 2){


            std::string v2 = "";
            if(BlueTooth::str!= NULL){

                v2+="receive data = \n"+BlueTooth::str->toStdString()+"\n";

                Sx::Instance()->setConsole(v2.c_str());
            }else{
                v2+="wait data = ...\n";

                Sx::Instance()->setConsole(v2.c_str());

            }

        }
    }
}
void Processer::task_01_001(){
    this->timer->stop();
    Sx::Instance()->setConsole("Bright all led");
    this->BrightAll();

}
void Processer::task_01_002(){

    Sx::Instance()->setConsole("Extinguish all led");
    this->ExtinguishAll();
    this->timer->stop();
}
void Processer::task_01_003(){
    Sx::Instance()->setConsole("do the count time");
    Sx::Instance()->timeCounter = 0;
    Sx::Instance()->setCode(1,3);
    this->timer->start(200);



}
void Processer::task_01_004(){
    this->timer->stop();
    Sx::Instance()->setCode(1,4);
    Sx::Instance()->timeCounter = 0;
    this->timer->start(200);
}
void Processer::task_01_005(){
    this->timer->stop();
    Sx::Instance()->setCode(1,5);
    Sx::Instance()->timeCounter = 0;
    this->timer->start(200);
}


void Processer::task_02_001(){


    Sx::Instance()->setCode(2,1);





}
void Processer::task_02_002(){

    PCF::init();

    this->timer->stop();
    Sx::Instance()->setCode(2,2);
    Sx::Instance()->timeCounter = 0;
    this->timer->start(50);

}

void Processer::task_02_003_01(){

    QStringList qsl = task_2_v3->text().split(";");
    task_2_v1 = atoi(qsl[0].toStdString().c_str());
    task_2_v2 = atoi(qsl[1].toStdString().c_str());
    Sx::Instance()->setCode(2,3);
//    qDebug()<<task_2_v1<<" "<<task_2_v2;

}
void Processer::task_02_003(){

    QDialog *qs = new QDialog(Sx::Instance());

    qs->resize(300,300);
    QPalette pl;
    pl.setColor(QPalette::Background,QColor(111,111,111));
    qs->setWindowTitle("Task2 Controller");
    QPushButton *q1 = new QPushButton(qs);
    q1->setGeometry(0,25,100,25);
    q1->setText("write");
    q1->show();
    QLineEdit *q2 = new QLineEdit(qs);
    q2->setGeometry(0,0,200,25);
    task_2_v3 = q2;
    QObject::connect(q1, SIGNAL(clicked()),this,SLOT(task_02_003_01()));



    qs->setPalette(pl);
    qs->show();

}


void Processer::task_03_001(){

    Sx::Instance()->setCode(3,1);
    Sx::Instance()->setConsole("listen the key down");

    Interrupt ite(3,[](){

        task_3_v1++;
        std::string value = "";
        value+= (" the value key1 plus and answer = "+QString::number(task_3_v1).toStdString()+"\n");
        value+=  (" the value key2 plus and answer = "+QString::number(task_3_v2).toStdString()+"\n");
        Sx::Instance()->setConsole(value.c_str());

        return 0;
    });
    Interrupt ite2(4,[](){
        task_3_v2--;
        std::string value = "";
        value+= (" the value key1 plus and answer = "+QString::number(task_3_v1).toStdString()+"\n");
        value+=  (" the value key2 plus and answer = "+QString::number(task_3_v2).toStdString()+"\n");
        Sx::Instance()->setConsole(value.c_str());

        return 0;
    });

    Interrupt ite3(5,[](){
        task_3_v1 = 0;
        task_3_v2 = 20;
        std::string value = "";
        value+= (" the value key1 plus and answer = "+QString::number(task_3_v1).toStdString()+"\n");
        value+=  (" the value key2 plus and answer = "+QString::number(task_3_v2).toStdString()+"\n");
        Sx::Instance()->setConsole(value.c_str());
        return 0;
    });



}

void Processer::task_04_001(){

    qDebug()<<"USE TASK4";
    Superaudible* super = new Superaudible(3,4);
    Sx::Instance()->setCode(4,1);
    this->timer->stop();
    this->timer->start(1);


}
void Processer::task_06_001(){

    BME280 *bme280 = new BME280(0x76);
    bme280->bme_init();
    Sx::Instance()->setCode(6,1);
    this->timer->stop();
    this->timer->start(100);
}
void Processer::task_07_001_1(){

    BlueTooth::getInstance()->send(task_2_v3->text().toStdString().c_str());
}
void Processer::task_07_001(){


    QDialog *qs = new QDialog(Sx::Instance());

    qs->resize(300,300);
    QPalette pl;
    pl.setColor(QPalette::Background,QColor(111,111,111));
    qs->setWindowTitle("Task7 send test");
    QPushButton *q1 = new QPushButton(qs);
    q1->setGeometry(0,25,100,25);
    q1->setText("write");
    q1->show();
    QLineEdit *q2 = new QLineEdit(qs);
    q2->setGeometry(0,0,200,25);
    task_2_v3 = q2;
    QObject::connect(q1, SIGNAL(clicked()),this,SLOT(task_07_001_1()));
    qs->show();
//    BlueTooth::getInstance()->send("2333");

}

void Processer::task_07_002(){

  char* val = BlueTooth::getInstance()->getData();
  Sx::Instance()->setCode(7,2);
  this->timer->stop();
  this->timer->start(100);
  BlueTooth::operation = [](QString* val){


      QStringList qsl = val->split("&");
        int index = 0;

        if(qsl[0] == "ex"){//extinguish the index light
            int index = qsl[1].toInt();
             LED::getInstance()->extinguishSingle(index);

        }

        if(qsl[0] == "bt"){//bright the index light
            int index = qsl[1].toInt();
            LED::getInstance()->brightSingle(index);

        }
        if(qsl[0] == "ex-all"){

            LED::getInstance()->extinguishAll();
        }
        if(qsl[0] == "bt-all"){

            LED::getInstance()->brightAll();
        }

      return 0;
  };
}
//open game

void Processer::task_08_001(){





}
//open camera
void Processer::task_09_001(){


    CameraSE::getInstance()->open();
}

//close camera
void Processer::task_09_002(){

    CameraSE::getInstance()->hide();
}

//detect camera
void Processer::task_09_003(){
    FileViewWidget::getInstance()->operation =[](QString* value){

        QImage img;
        img.load(*value);
        QImage qs = FaceSir::getInstance()->process(&img);
        QLabel *ql = new QLabel();
        ql->resize(400,400);
        qDebug()<<*value;
//    label->setPixmap(QPixmap::fromImage(image)); //显示一帧图像
        ql->setPixmap(QPixmap::fromImage(qs));
        ql->show();
        return 0;
    };
    FileViewWidget::getInstance()->showDialog();

}
void Processer::task_10_001(){

    Calculator* cal = new Calculator();
    cal->show();


}

void Processer::task_12_001(){

    MP3::getInstance()->show();


}
