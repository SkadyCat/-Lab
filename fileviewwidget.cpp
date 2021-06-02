#include "fileviewwidget.h"
#include<QTextCodec>
#include<QDebug>
#include<functional>
#include<vector>
#include<iostream>
#include<QString>
std::function<int(QString*)> FileViewWidget::operation = NULL;
FileViewWidget::FileViewWidget(QWidget *parent/*=0*/) :QWidget(parent)
{
    //—–实例化对象
    fileLineEdit = new QLineEdit("/home/pi/Desktop", this);
    fileListWidget = new QListWidget(this);

    //—布局
    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(fileLineEdit);
    vLayout->addWidget(fileListWidget);

    //–设置对应信号与槽
    connect(fileLineEdit, SIGNAL(returnPressed()),
                this, SLOT(slotDirShow(QDir)));
    connect(fileListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
                this, SLOT(slotDirShow(QListWidgetItem*)));

}


FileViewWidget * FileViewWidget::Instance = NULL;
FileViewWidget * FileViewWidget::getInstance(){

    if(Instance == NULL){

        Instance = new FileViewWidget();
    }

    return Instance;
};
void FileViewWidget::showDialog(){
    this->show();
    QString rootStr = "/home/pi/Desktop";
    QDir rootDir(rootStr);
    QStringList stringlist;
    stringlist << "*";
    list = rootDir.entryInfoList(stringlist);
    showFileInfoList(list);

    //—显示布局
    setLayout(vLayout);
    //—-设置窗口属性
    setWindowTitle("File View");
}
//–显示当前目录下的所有文件
void FileViewWidget::slotShow(QDir dir)
{
     QStringList stringList;
     stringList << "*";
     QFileInfoList InfoList = dir.entryInfoList(stringList, QDir :: AllEntries, QDir :: DirsFirst);
     showFileInfoList(InfoList);
}

//—用双击浏览器中显示的目录进入下一级，或者返回上一级目录。
void FileViewWidget::showFileInfoList(QFileInfoList list)
{
    //–清空列表控件
    fileListWidget->clear();

    //—-取出所有项，按照目录，文件方式添加到控件内
    for (unsigned int i = 0; i < list.count(); i++)
    {
        QFileInfo tmpFileInfo = list.at(i);
        if (tmpFileInfo.isDir())
        {
            QIcon icon("dir.png");
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem*tmpListWidgetItem = new QListWidgetItem(icon, fileName);
            fileListWidget->addItem(tmpListWidgetItem);
        }
        else
        {
            QIcon icon("file.png");
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem*tmpListWidgetItem = new QListWidgetItem(icon, fileName);
            fileListWidget->addItem(tmpListWidgetItem);
        }
    }
}


//—-根据用户的选择显示下一级目录下的文件，
void FileViewWidget::slotDirShow(QListWidgetItem *Item)
{

    //—-保存下一级目录名
    QString head = fileLineEdit->text();
    head.append("/");
    QString string = Item->text();
    head.append(string);
    QDir dir;
    //—-设置路径为当前目录路径
    dir.setPath(fileLineEdit->text());
    //—–重新设置路径
    dir.cd(string);
    //—-更新当前显示路径， 这里获取的是绝对路径
    fileLineEdit->setText(dir.absolutePath());
    //—显示当前文件目录下的所有文件
    slotShow(dir);

    if(operation!= NULL){


        if(string.contains("png")||string.contains("mp3")){

            operation(&head);
        }


    }

}
