#ifndef SX_H
#define SX_H


#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
#include <QLabel>
#include<QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include"threadsir.h"
#include<QCloseEvent>
class Sx : public QMainWindow
{
    Q_OBJECT

public:
    void closeEvent(QCloseEvent *event);
    static Sx* getInstance();
    void mousePressEvent(QMouseEvent *event);
    void debug(const char* value);
    int mainCode;
    int subCode;
    int timeCounter;
    int portPointer;
    void setCode(int mainCode,int subCode);
    ThreadSir *threadSir;
    static int closeStatu;
    void setConsole(const char* value);

    std::string toStdStr(QString val);

    Ui::MainWindow *ui;
    QLabel *label;
    QLabel *consoleLabel;

    QMenu* menu[3];
    QToolBar* menuBar ;


    QAction* act[10];

    QStatusBar* status ;
        Sx();

       ~Sx();



signals:

    void clickEvent_001();
    public slots:

    void clickEvent_001Process();
    void btn_0001Process();
    void timerUpDate();
public slots:
    void trigger0001();

private:
    static Sx* ins;
public:
    static Sx* Instance();


};

#endif // SX_H
