#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main(){ 
    Mat background1 = Mat(300,300,CV_8UC3,Scalar(0,0,0));//定义三个空白的图片
    Mat background2 = background1.clone();
    Mat background3 = background1.clone();

    circle(background1,Point(150,150),50,Scalar(255,255,255),2); 
    line(background2,Point(55,55),Point(245,245),Scalar(255,255,255),4);
    rectangle(background3,Rect(50,50,150,150),CV_RGB(255,255,255),3);
     //调用circle，line,rectangle函数，实现绘画功能
    imshow("line",background2);
    imshow("circle",background1);
    imshow("rectangle",background3);
    waitKey(0);
}
