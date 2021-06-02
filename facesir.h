#ifndef FACESIR_H
#define FACESIR_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
#include<QImage>
#include<QLabel>
class FaceSir
{

private:
    static FaceSir* Instance;

public:
    FaceSir();
    static FaceSir* getInstance();
    CascadeClassifier faceCascader; //分类器
    QImage process(QImage* input);
    QLabel* label;


};

#endif // FACESIR_H
