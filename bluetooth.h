#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include<functional>
#include<vector>
#include<iostream>
#include<QString>
class BlueTooth
{
public:
    BlueTooth();
    static BlueTooth* Instance;
    void send();
    void send(const char* data);
    char* getData();
    static char* cahce;
    static char* data;
    static int pointer;
    static BlueTooth* getInstance();
    static QString *str;
    static int flag;
    static std::function<int(QString*)> operation;
    static int* Ox2Binary(int value);
};

#endif // BLUETOOTH_H
