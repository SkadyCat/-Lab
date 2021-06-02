#ifndef PROCESSER_H
#define PROCESSER_H


#include<QLabel>
#include<QWidget>
#include<QTimer>
#include<QLineEdit>
class Processer:public QLabel
{
    Q_OBJECT
public:
    Processer(QWidget *parent);
    Processer();
    void BrightAll();
    void ExtinguishAll();
    QTimer *timer;
    static Processer * Instance;
    void threadEvent(int mainCode,int subCode);


signals:


public slots:


    void updateProcess();
    void task_01_001();
    void task_01_002();
    void task_01_003();
    void task_01_004();
    void task_01_005();

    void task_02_001();
    void task_02_002();
    void task_02_003();
    void task_02_003_01();

    void task_03_001();

    void task_04_001();

    void task_06_001();

    void task_07_001();
    void task_07_001_1();
    void task_07_002();

    void task_08_001();

    void task_09_001();
    void task_09_002();
    void task_09_003();
    void task_10_001();

    void task_12_001();
};

#endif // PROCESSER_H
