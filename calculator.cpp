#include "calculator.h"
#include "ui_calculator.h"
#include<QDebug>

#define add 1
#define sub 2
#define div 3
#define mul 4

Calculator::Calculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    frontValue = "0";
    showNum();
}



Calculator::~Calculator()
{
    delete ui;
}
void Calculator::showNum(){


    ui->console->setText(frontValue);

}


QString Calculator::preValue(){


    if(frontValue == "0")
    {
        return QString();
    }

    return frontValue;
}
void Calculator::on_click_1_clicked()
{

    QString val = ui->click_1->text();
    frontValue = preValue().append(val);
    ui->console->setText(frontValue);


}

void Calculator::on_click_2_clicked()
{
    QString val = ui->click_2->text();
    frontValue = preValue().append(val);
    ui->console->setText(frontValue);
}

void Calculator::on_click_3_clicked()
{
    QString val = ui->click_3->text();
    frontValue = preValue().append(val);
    ui->console->setText(frontValue);
}

void Calculator::on_click_6_clicked()
{ QString val = ui->click_6->text();
    frontValue = preValue().append(val);
    ui->console->setText(frontValue);

}

void Calculator::on_click_5_clicked()
{
    QString val = ui->click_5->text();
    frontValue = preValue().append(val);
    ui->console->setText(frontValue);
}

void Calculator::on_click_4_clicked()
{
    QString val = ui->click_4->text();
    frontValue = preValue().append(val);
    ui->console->setText(frontValue);
}

void Calculator::on_click_7_clicked()
{
    QString val = ui->click_7->text();
    frontValue = preValue().append(val);
    ui->console->setText(frontValue);
}

void Calculator::on_click_8_clicked()
{
    QString val = ui->click_8->text();
    frontValue = preValue().append(val);
    ui->console->setText(frontValue);
}

void Calculator::on_click_9_clicked()
{
    QString val = ui->click_9->text();
    frontValue = preValue().append(val);
    ui->console->setText(frontValue);
}

void Calculator::on_plus_clicked()
{

     backValue = frontValue;
     frontValue = "0";
     ui->console->setText(frontValue);
     opCode = add;
}

void Calculator::on_equal_clicked()
{
    double v1 = frontValue.toDouble();
    double v2 = backValue.toDouble();
    double v3 = 0;
    switch(opCode){
        case add:

            v3 = v1+v2;


        break;

    case sub:
            v3 =  v2 - v1;
        break;

    case div:
            v3 = v2/v1;
        break;

    case mul:
            v3 = v1*v2;
        break;





    }
    frontValue = QString::number(v3);
    backValue = "0";
     showNum();
}

void Calculator::on_point_clicked()
{

    if(frontValue.contains(".")){
        return;
    }
    QString val = ui->click_9->text();
    frontValue = preValue().append(".");
    ui->console->setText(frontValue);
}

void Calculator::on_clear_clicked()
{
    frontValue = "0";
    backValue = "0";
     ui->console->setText(frontValue);
}

void Calculator::on_sub_clicked()
{
    backValue = frontValue;
    frontValue = "0";
    ui->console->setText(frontValue);
    opCode = sub;
}

void Calculator::on_mul_clicked()
{
    backValue = frontValue;
    frontValue = "0";
    ui->console->setText(frontValue);
    opCode = mul;
}

void Calculator::on_div_clicked()
{
    backValue = frontValue;
    frontValue = "0";
    ui->console->setText(frontValue);
    opCode = div;
}

void Calculator::on_change_clicked()
{
    if(frontValue.contains("-")){

        frontValue = frontValue.remove("-");

    }else {

        frontValue = QString("-").append(preValue());
}
    showNum();
}
