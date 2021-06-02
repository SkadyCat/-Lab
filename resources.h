#ifndef RESOURCES_H
#define RESOURCES_H

#include<QMap>
#include<QImage>
#include<QString>
#include<QPalette>
class Resources
{
private :
    static Resources* Instance;
public:
    static Resources* getInstance();
    Resources();
    QMap<QString,QImage*> *map;
    QImage* load(QString name);
    QImage* load(QString name,int w,int h);
    QPalette getQPallete(QString path,int w,int h);
};

#endif // RESOURCES_H
