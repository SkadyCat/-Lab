#ifndef SUPERAUDIBLE_H
#define SUPERAUDIBLE_H

#define WAIT_HIGHT 1
#define WAIT_LOW 2
#define SENDER_MESSAGE 0
class Superaudible
{
public:
    Superaudible();
    Superaudible(int Trig,int Echo);
    static int doorCat;
    static Superaudible* Instance;
    float distance;
    int Trig;
    int Echo;
    long counter;
    void beginSendWave();
    static int statu;
    void shutDown();
    int read(int port);
    void waitLowMessage();
    void waitHightMessage();
    float countDistance();
};

#endif // SUPERAUDIBLE_H
