#include "resources.h"
#include<QDebug>
Resources::Resources()
{
    map = new QMap<QString,QImage*>();
}

Resources* Resources::Instance = nullptr;

Resources* Resources::getInstance(){

    if(Instance == nullptr){

        Instance = new Resources();
    }
    return Instance;

};


QImage* Resources::load(QString name){


    if(map->contains(name)){

        return map->value(name);
    }

    QString path(":/res/img/");
    path = path.append(name);
    path = path.append(".png");
    QImage *qm = new QImage();
    qm->load(path);
    map->insert(name,qm);
    qDebug()<<path;
    return qm;

}

QPalette Resources::getQPallete(QString path,int w,int h){

    QImage * img = load(path,w,h);
    QPalette qpl;
    qpl.setBrush(QPalette::Background,QBrush(QPixmap::fromImage(*img)));

    return qpl;
}
QImage* Resources::load(QString name,int w,int h){



    if(map->contains(name)){

        return map->value(name);
    }

    QString path(":/res/img/");
    path = path.append(name);
    path = path.append(".png");
    QImage *qm = new QImage();
    QImage q2;
    q2.load(path);
    q2 = q2.scaled(w,h);

    qm = new QImage(q2);

    map->insert(name,qm);

    return map->value(name);

}
