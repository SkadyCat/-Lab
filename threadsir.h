#ifndef THREADSIR_H
#define THREADSIR_H


#include<QThread>
class ThreadSir :public QThread
{
    Q_OBJECT
public:
    ThreadSir();
    void close();
protected:
    void run();



};

#endif // THREADSIR_H
