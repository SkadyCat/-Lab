#ifndef WRITETOOL_H
#define WRITETOOL_H

#define	INPUT			 0
#define	OUTPUT			 1
#define	LOW              0
#define	HIGH			 1
class WriteTool
{

private:
    static WriteTool * ins;
public:
    WriteTool();

    static WriteTool *Instance();

    void setMode(int port,int value);
    void setGPIO(int port,int value);
    //微秒级延迟
    void delay_01(int value);

    int getGPIO(int port);
};

#endif // WRITETOOL_H
