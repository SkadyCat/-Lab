#ifndef READER_H
#define READER_H

#include<QFile>
#include<QString>

class Reader
{
public:
    Reader();
public:
    static QString getStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        QString qv = qss.readAll();
        qss.close();
        return qv;
    }
};

#endif // READER_H
