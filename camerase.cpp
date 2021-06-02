#include "camerase.h"
#include<QTimer>
#include<QObject>
#include<QWidget>
#include<QLabel>
#include<QDebug>
CameraSE::CameraSE()
{

    String file = "/home/pi/Desktop/OPenCV/opencv-3.4.3/data/haarcascades_cuda/haarcascade_frontalface_alt.xml";
    faceCascader.load(file); //使用的人脸检测分类器的地址
    this->resize(600,600);
    label = new QLabel(this);
    label->setGeometry(0,0,600,600);
    QPalette qp;
    qp.setColor(QPalette::Background,QColor(111,111,111));
    // pl.setColor(QPalette::Background,QColor(111,111,111));

    label->setPalette(qp);
//    label->show();

}

CameraSE* CameraSE::Instance = NULL;
CameraSE* CameraSE::getInstance(){

    if(Instance == NULL){

        Instance= new CameraSE();

    }

    return Instance;

}
void CameraSE::open(){

     capture = cvCreateCameraCapture(0); //打开摄像头
     timer = new QTimer(this); //新建一个定时器
     image = new QImage();
     connect(timer, SIGNAL(timeout()), this, SLOT(update()));
     timer->start(50); //50ms 获取一帧图像
     qDebug()<<"open";
     this->show();
     update();
}

void CameraSE::close(){
    this->hide();
    timer->stop();

}

void CameraSE::update(){

     std::vector<Rect> faces;
     frame = cvQueryFrame(capture); //获取一帧图像
     Mat mat_frame= cvarrToMat(frame); //mat 格式用于人脸检测
     cvtColor(mat_frame, gray, COLOR_BGR2GRAY); //灰度转换
     faceCascader.detectMultiScale(gray, faces, 1.2, 3, 0, Size(30, 30)); //获取人脸数据，faces 即为人脸
     for(int i = 0; i < faces.size(); i++){
         rectangle(mat_frame, faces[static_cast<int>(i)], Scalar(0, 255, 0), 2, 8, 0); //圈出该帧图像中的所有人脸

     }
     QImage image = QImage((const uchar*)frame->imageData,
     frame->width, frame->height,
     QImage::Format_RGB888).rgbSwapped(); //格式转换，将 BGR 转换为 RGB
     label->setPixmap(QPixmap::fromImage(image)); //显示一帧图像

}
