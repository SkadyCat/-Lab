#ifndef INTERRUPT_H
#define INTERRUPT_H

#include<functional>
#include<vector>
#include<iostream>
//author ljy qq:874212844
class Interrupt
{

private:

public:

    Interrupt();
    Interrupt(int gpioPort);
    Interrupt(int gpioPort,std::function<int()> operation);
    static Interrupt* arr;
    static int pointer;
    static void initInterrupt();
    int index;
    int gpioPort;
    static int workGpioNum;
    static int* workGpioPort;


    static void setWorkGpioArr(){
        workGpioNum = 40;
        workGpioPort = new int[40];
        for(int i =0;i<40;i++){

            workGpioPort[i] = -1;
        }

    }
    /**
     * @brief initKey  init key process
     * @param gpioPort the input gpio port code
     */
    void initKey(int gpioPort);


    std::function<int()> f;
    void setFunc(std::function<int()> operation);
     void op();
};

#endif // INTERRUPT_H
