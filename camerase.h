#ifndef CAMERASE_H
#define CAMERASE_H
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
#include<QImage>
#include<QDialog>
#include<QWidget>
#include<QLabel>
class CameraSE:public QDialog
{
        Q_OBJECT


public:
     CameraSE();
     CameraSE(QWidget* parent);
     QImage *image;
     CvCapture *capture; //处理摄像头图像的结构体
     IplImage *frame; //一帧图像
     Mat gray; //mat 格式的灰度图
     QTimer *timer;
     CascadeClassifier faceCascader; //分类器
     void open();
     void close();

     QLabel *label;
     static CameraSE * getInstance();
private:
     static CameraSE * Instance;
public slots:
     void update();

};

#endif // CAMERASE_H
