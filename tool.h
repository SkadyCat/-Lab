#ifndef TOOL_H
#define TOOL_H

#define HIGH = 1
#define LOW = 0
class Tool
{
public:
    Tool();
    Tool* Instance();
    void pinMode(int port,int value);
    void write(int port,int value);

private:
    static Tool *ins;


};

#endif // TOOL_H
