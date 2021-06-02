#include "opencvtool.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

OpencvTool::OpencvTool()
{


        UMat frame;
        CvCapture *capture = cvCreateCameraCapture(0);
        imshow("摄像头图像", frame);


}
