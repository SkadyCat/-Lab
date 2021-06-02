#ifndef PCF_H
#define PCF_H


class PCF
{
public:
    PCF();
    static void init();
    static int read();
    static int path[];
    static int address;
    static int fd;
    static int pointer;
    static int data[];
    static int index;
    static void toIntArr(int* container,int value);
};

#endif // PCF_H
