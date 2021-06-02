#ifndef FILEVIEWWIDGET_H
#define FILEVIEWWIDGET_H

#include <QWidget>
#include <QDir>
#include <QListWidgetItem>
#include <QFileInfoList>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QIcon>
#include <QStringList>
#include<functional>
#include<vector>
#include<iostream>
#include<QString>
class FileViewWidget : public QWidget
{
    Q_OBJECT

private:
    static FileViewWidget* Instance;
public:
    FileViewWidget(QWidget *parent=0);
    static FileViewWidget* getInstance();
    //—用双击浏览器中显示的目录进入下一级，或者返回上一级目录。
    void showFileInfoList(QFileInfoList list);
    static std::function<int(QString*)> operation;
public slots:
        //–显示当前目录下的所有文件
    void slotShow(QDir dir);

     //—-根据选择显示下一级目录下的文件，
    void slotDirShow(QListWidgetItem *Item);
    void showDialog();


private:
    QLineEdit *fileLineEdit;
    QListWidget *fileListWidget;
    QVBoxLayout *vLayout;
    QFileInfoList list;
};

#endif // FILEVIEWWIDGET_H
