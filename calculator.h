#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

namespace Ui {
class Calculator;
}

class Calculator : public QWidget
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
     Ui::Calculator *ui;
     char showstr[100];
     QString frontValue;
     QString backValue;
     double a = 0;
     double b = 0;
     double ans = 0;
     int opCode = 0;
//     int cha = 0, wei = 10, showlen=0, oper;
//     bool sign = false, signdian = false, starta = false, startb =
//     false, signa = true, signb = true;
public:
     void showNum();
     QString preValue();
private slots:

      void on_click_1_clicked();
      void on_click_2_clicked();
      void on_click_3_clicked();
      void on_click_6_clicked();
      void on_click_5_clicked();
      void on_click_4_clicked();
      void on_click_7_clicked();
      void on_click_8_clicked();
      void on_click_9_clicked();

      void on_plus_clicked();

      void on_equal_clicked();
      void on_point_clicked();
      void on_clear_clicked();
      void on_sub_clicked();
      void on_mul_clicked();
      void on_div_clicked();
      void on_change_clicked();
};

#endif // CALCULATOR_H
