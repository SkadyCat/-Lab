#include "mainwindow.h"
#include "reader.h"

#include <QApplication>
#include"sx.h"
#include<QHBoxLayout>
#include<QPushButton>
#include<QRect>
#include<QtGui>
#include<QLabel>
#include<QMenuBar>
#include<QToolBar>
#include "processer.h"
#include"writetool.h"
#include "threadsir.h"
#include"interrupt.h"
#include"camerase.h"
#include"fileviewwidget.h"
//#include"opencvtool.h"
int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    Sx w;
    Interrupt::setWorkGpioArr();
    w.setFixedSize(600,500);
    QMenuBar qm(&w);
    WriteTool tool;
    Processer processer;
    ThreadSir thread;
    w.threadSir = &thread;


    QMenu q1("Task");
    QMenu q2("Tool");
    QMenu task1("task_01");
    QMenu task2("task_02");
    QMenu task3("task_03");
    QMenu task4("task_04");
    QMenu task5("task_05");
    QMenu task6("task_06");
    QMenu task7("task_07");

    QMenu task8("task_08");
    QMenu task9("task_09");
    QMenu task10("task_10");
    QMenu task12("task_12");

    QMenu tool1("FileDialog");
    q2.addMenu(&tool1);
    qm.addMenu(&q1);
    qm.addMenu(&q2);
    q1.addMenu(&task1);
    q1.addMenu(&task2);
    q1.addMenu(&task3);
    q1.addMenu(&task4);
    q1.addMenu(&task5);
    q1.addMenu(&task6);
    q1.addMenu(&task7);
    q1.addMenu(&task8);
    q1.addMenu(&task9);
    q1.addMenu(&task10);
    q1.addMenu(&task12);

    QAction* qa_task_01_001 =task1.addAction("BrightAll");
    QAction* qa_task_01_002 =task1.addAction("ExtinguishAll");
    QAction* qa_task_01_003 =task1.addAction("mode_1");
    QAction* qa_task_01_004 =task1.addAction("mode_2");
    QAction* qa_task_01_005 =task1.addAction("mode_3");

    QAction* qa_task_02_001 =task2.addAction("mode_1");
    QAction* qa_task_02_002 =task2.addAction("mode_2");
    QAction* qa_task_02_003 =task2.addAction("mode_3");

    QAction* qa_task_03_001 =task3.addAction("mode_1");

    QAction* qa_task_04_001 =task4.addAction("mode_1");


    QAction* qa_task_06_001 =task6.addAction("mode_1");

    QAction* qa_task_07_001 =task7.addAction("send_data");
    QAction* qa_task_07_002 =task7.addAction("receive_data");


    QAction* qa_task_09_001 =task9.addAction("open");
    QAction* qa_task_09_002 =task9.addAction("close");
    QAction* qa_task_09_003 =task9.addAction("imgProcess");

    QAction* qa_task_10_001 =task10.addAction("calculator");
         QAction* qa_task_12_001 =task12.addAction("mp3");

    QLabel qlabel(&w);

    qlabel.setText("console:");
    qlabel.setGeometry(0,400,200,20);
    QLabel qConsole(&w);
    qConsole.setGeometry(0,420,600,140);
    qConsole.setAlignment(Qt::AlignTop);
    qConsole.setText("hello to using raspberry controller");
    w.consoleLabel = &qConsole;
    thread.start();
    w.show();


    QObject::connect(qa_task_01_001,SIGNAL(triggered()),&processer,SLOT(task_01_001()));
    QObject::connect(qa_task_01_002,SIGNAL(triggered()),&processer,SLOT(task_01_002()));
    QObject::connect(qa_task_01_003,SIGNAL(triggered()),&processer,SLOT(task_01_003()));
    QObject::connect(qa_task_01_004,SIGNAL(triggered()),&processer,SLOT(task_01_004()));
    QObject::connect(qa_task_01_005,SIGNAL(triggered()),&processer,SLOT(task_01_005()));

    QObject::connect(qa_task_02_001,SIGNAL(triggered()),&processer,SLOT(task_02_001()));
    QObject::connect(qa_task_02_002,SIGNAL(triggered()),&processer,SLOT(task_02_002()));
    QObject::connect(qa_task_02_003,SIGNAL(triggered()),&processer,SLOT(task_02_003()));

    QObject::connect(qa_task_03_001,SIGNAL(triggered()),&processer,SLOT(task_03_001()));

    QObject::connect(qa_task_04_001,SIGNAL(triggered()),&processer,SLOT(task_04_001()));
    //--task-6//
    QObject::connect(qa_task_06_001,SIGNAL(triggered()),&processer,SLOT(task_06_001()));
    //--task-7//
    QObject::connect(qa_task_07_001,SIGNAL(triggered()),&processer,SLOT(task_07_001()));
    QObject::connect(qa_task_07_002,SIGNAL(triggered()),&processer,SLOT(task_07_002()));

    //task-9//
    QObject::connect(qa_task_09_001,SIGNAL(triggered()),&processer,SLOT(task_09_001()));
    QObject::connect(qa_task_09_002,SIGNAL(triggered()),&processer,SLOT(task_09_002()));
    QObject::connect(qa_task_09_003,SIGNAL(triggered()),&processer,SLOT(task_09_003()));

    QObject::connect(qa_task_10_001,SIGNAL(triggered()),&processer,SLOT(task_10_001()));

     QObject::connect(qa_task_12_001,SIGNAL(triggered()),&processer,SLOT(task_12_001()));
    QTimer timer;

    QObject::connect(&timer,SIGNAL(timeout()),&processer,SLOT(updateProcess()));



    processer.timer = &timer;

    qm.setStyleSheet(Reader::getStyle(":/Qss/demo.qss"));
    q1.setStyleSheet(Reader::getStyle(":/Qss/menu.qss"));
    task1.setStyleSheet(Reader::getStyle(":/Qss/menu.qss"));
    qConsole.setStyleSheet(Reader::getStyle(":/Qss/console.qss"));
    return a.exec();
}
